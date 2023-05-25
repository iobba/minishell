/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:36:07 by iobba             #+#    #+#             */
/*   Updated: 2023/03/06 15:20:26 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	asterisk_case(int *fd_in, int *fd_out)
{
	if (*fd_in > 0)
		close(*fd_in);
	if (*fd_out > 1)
		close(*fd_out);
	print_error("minishell: : ambiguous redirect", "", "");
	return (EXIT_FAILURE);
}

int	close_and_open(int *fd, char *filename, int type)
{
	if (type == dless || type == less)
	{
		if (*fd > 0)
			close(*fd);
		*fd = open(filename, O_RDONLY);
		if (*fd < 0)
			return (EXIT_FAILURE);
	}
	if (type == great)
	{
		if (*fd > 1)
			close(*fd);
		*fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*fd < 0)
			return (EXIT_FAILURE);
	}
	if (type == dgreat)
	{
		if (*fd > 1)
			close(*fd);
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	manage_redirections(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_io_redirect	*redi;

	redi = cmd->redi_list;
	while (redi)
	{
		if (redi->io_redirect == dless)
			if (close_and_open(fd_in, cmd->here_doc, dless))
				return (error_errno(cmd->here_doc), EXIT_FAILURE);
		if (redi->io_redirect == less)
			if (close_and_open(fd_in, redi->filename, less))
				return (error_errno(redi->filename), EXIT_FAILURE);
		if (redi->io_redirect == great)
			if (close_and_open(fd_out, redi->filename, great))
				return (error_errno(redi->filename), EXIT_FAILURE);
		if (redi->io_redirect == dgreat)
			if (close_and_open(fd_out, redi->filename, dgreat))
				return (error_errno(redi->filename), EXIT_FAILURE);
		if (redi->io_redirect == 0)
			return (asterisk_case(fd_in, fd_out));
		redi = redi->next;
	}
	return (EXIT_SUCCESS);
}

int	set_in_out_fds(t_cmd *cmd, int *fd_in, int *fd_out)
{
	int	fd[2];

	cmd->in_of_next = 0;
	*fd_in = 0;
	if (cmd->prev)
		*fd_in = cmd->prev->in_of_next;
	*fd_out = 1;
	if (cmd->sep == pipe_op)
	{
		if (pipe(fd) == -1)
			error_exit("minishell");
		*fd_out = fd[1];
		cmd->in_of_next = fd[0];
	}
	return (manage_redirections(cmd, fd_in, fd_out));
}
