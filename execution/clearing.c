/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:04:36 by iobba             #+#    #+#             */
/*   Updated: 2023/03/08 16:01:12 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	clear_redir(t_io_redirect **lst)
{
	t_io_redirect	*head;
	t_io_redirect	*to_del;

	if (!lst)
		return ;
	head = *lst;
	while (head)
	{
		to_del = head;
		head = head->next;
		if (to_del->io_redirect == dless)
			free(to_del->here_end);
		else
			free(to_del->filename);
		free(to_del);
	}
	*lst = NULL;
}

void	free_here_doc(t_cmd	*to_del)
{
	unlink(to_del->here_doc);
	free(to_del->here_doc);
}

void	clear_cmds(t_cmd **lst)
{
	t_cmd	*head;
	t_cmd	*to_del;
	char	**args;

	head = *lst;
	while (head)
	{
		to_del = head;
		head = head->next;
		free(to_del->cmd);
		args = to_del->args;
		while (*args)
		{
			free(*args);
			args++;
		}
		free(to_del->args);
		if (to_del->here_doc)
			free_here_doc(to_del);
		clear_redir(&(to_del->redi_list));
		free(to_del);
	}
	*lst = NULL;
}

int	clear_all(t_general *all)
{
	clear_cmds(&(all->all_cmds));
	return (EXIT_SUCCESS);
}
