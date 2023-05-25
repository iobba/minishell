/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:33:14 by iobba             #+#    #+#             */
/*   Updated: 2023/03/08 15:30:27 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_name_here_doc(int i)
{
	char	*tty;
	char	*diff;
	char	*name;
	char	*name_1;

	diff = ft_itoa(i);
	tty = ttyname(0);
	name_1 = ft_strjoin("/tmp/.", tty + 9);
	name = ft_strjoin_free(name_1, diff);
	return (name);
}

int	here_doc_child(t_io_redirect *redi, char *name, t_general *all)
{
	int		fd;
	char	*line;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("minishell");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, redi->here_end, ft_strlen(redi->here_end) + 1))
			break ;
		if (redi->here_doc_expand)
			here_doc_expansion(&line, all);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}

int	set_here_doc(t_io_redirect *redi, char *name, t_general *all)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("minishell");
	else if (pid == 0)
		here_doc_child(redi, name, all);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &status, 0) == -1)
			return (error_errno("minishell: waitpid"), EXIT_FAILURE);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (EXIT_FAILURE);
		if (WIFEXITED(status) && WEXITSTATUS(status))
			exit(WEXITSTATUS(status));
	}
	return (EXIT_SUCCESS);
}

int	fill_here_doc(t_general *all)
{
	t_cmd			*cmd;
	t_io_redirect	*redi;
	int				i;

	cmd = all->all_cmds;
	i = 0;
	while (cmd)
	{
		redi = cmd->redi_list;
		while (redi)
		{
			if (redi->io_redirect == dless)
			{
				if (!cmd->here_doc)
					cmd->here_doc = get_name_here_doc(i);
				if (set_here_doc(redi, cmd->here_doc, all))
					return (EXIT_FAILURE);
			}
			redi = redi->next;
		}
		i++;
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
