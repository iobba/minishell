/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:39:20 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:39:24 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	show_tokens(t_list *tokens)
{
	printf("______________\n");
	while (tokens)
	{
		printf("token: %s\n", tokens->content);
		tokens = tokens->next;
	}
	printf("______________\n");
}

void	show_redis(t_io_redirect *list)
{
	while (list)
	{
		if (list->io_redirect == less)
			printf("<%s\n", list->filename);
		else if (list->io_redirect == great)
			printf(">%s\n", list->filename);
		else if (list->io_redirect == dgreat)
			printf(">>%s\n", list->filename);
		else if (list->io_redirect == dless)
		{
			printf("<<%s\n", list->here_end);
			printf("heredoc_expand: %i\n", list->here_doc_expand);
		}
		else if (!(list->io_redirect))
			printf("ambigous red\n");
		list = list->next;
	}
}

void	show_cmds(t_cmd *cmds)
{
	char	**arr;
	t_cmd	*tmp;

	printf("\n\n");
	tmp = NULL;
	while (cmds)
	{
		printf("*****************\n");
		printf("cmd: %s\n", cmds->cmd);
		arr = cmds->args;
		while (*arr)
		{
			printf("args: %s\n", *arr);
			arr++;
		}
		printf("sep: %i\n", cmds->sep);
		printf("level: %i\n", cmds->level);
		show_redis(cmds->redi_list);
		printf("*******************\n");
		tmp = cmds;
		cmds = cmds->next;
	}
	printf("\n\n");
}
