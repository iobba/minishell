/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:40:17 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:40:20 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	remove_redirect(t_list **tks, t_list **head, t_list *prev)
{
	t_list	*tmp;

	if (!prev)
	{
		tmp = (*tks)->next;
		ft_lstdelone(*tks, free);
		*tks = tmp;
		tmp = (*tks)->next;
		free(*tks);
		*tks = tmp;
		*head = *tks;
	}
	else
	{
		tmp = (*head)->next->next;
		free((*head)->next);
		ft_lstdelone(*head, free);
		prev->next = tmp;
		*head = prev;
	}
}

void	init_redir_elem(t_io_redirect **redir_elem, int redir)
{
	*redir_elem = malloc(sizeof(t_io_redirect));
	if (!(*redir_elem))
		error_exit("iishell");
	(*redir_elem)->io_redirect = redir;
	(*redir_elem)->next = NULL;
}

void	handle_redir(t_list *tks, t_general *all, t_io_redirect *redir_elem)
{
	int				nbr_quotes;
	int				nbr_split;
	int				nbr_matchs;

	param_expansion(tks->next, all, &nbr_split);
	if (!gllobing(tks->next, &nbr_matchs))
	{
		nbr_quotes = count_quotes(tks->next->content);
		tks->next->content = remove_quotes(tks->next->content, nbr_quotes);
	}
	if (nbr_split < 0 || nbr_split >= 1 || nbr_matchs > 1)
		redir_elem->io_redirect = 0;
	else
		redir_elem->filename = tks->next->content;
}

void	add_redir(int redir, t_list *tks, t_io_redirect **list, t_general *all)
{
	t_io_redirect	*redir_elem;
	int				nbr_quote;
	int				nbr_split;
	int				nbr_matchs;

	init_redir_elem(&redir_elem, redir);
	if (redir == dless)
	{
		nbr_quote = count_quotes(tks->next->content);
		redir_elem->here_doc_expand = (nbr_quote == 0);
		redir_elem->here_end = tks->next->content;
		if (nbr_quote)
			redir_elem->here_end = remove_quotes(tks->next->content, nbr_quote);
	}
	else
		handle_redir(tks, all, redir_elem);
	ft_redi_add_back(list, redir_elem);
}

void	fill_redir(t_general *all, t_list **tks, t_io_redirect **redir_list)
{
	int		redir;
	t_list	*head;
	t_list	*prev;

	prev = NULL;
	head = *tks;
	while (head)
	{
		redir = is_redir(head->content);
		if (redir)
		{
			add_redir(redir, head, redir_list, all);
			remove_redirect(tks, &head, prev);
		}
		else
		{
			prev = head;
			head = head->next;
		}
		if (head)
			redir = is_redir(head->content);
	}
}
