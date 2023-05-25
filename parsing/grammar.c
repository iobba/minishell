/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:40:09 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:40:12 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	gllob_tokens(t_list *tokens)
{
	int	nbr_matchs;
	int	nbr_quotes;

	while (tokens)
	{
		if (!gllobing(tokens, &nbr_matchs))
		{
			nbr_quotes = count_quotes(tokens->content);
			tokens->content = remove_quotes(tokens->content, nbr_quotes);
		}
		while (nbr_matchs > 1 && tokens)
		{
			nbr_matchs--;
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
}

void	entitle_tokens(t_general *all, t_list *tokens, int sep, int *lvl)
{
	t_cmd	*cmd_elem;
	t_list	*head;
	int		redir;
	int		o_parenth;
	int		c_parenth;

	o_parenth = 0;
	c_parenth = 0;
	init_cmd_elem(&cmd_elem, sep);
	skip_parenth(&tokens, &o_parenth, &c_parenth);
	fill_redir(all, &tokens, &(cmd_elem->redi_list));
	head = tokens;
	if (head)
	{
		while (head->next && !is_curly(head->next->content))
			head = head->next;
		skip_parenth(&(head->next), &o_parenth, &c_parenth);
		head->next = NULL;
	}
	expand_tokens(all, tokens);
	gllob_tokens(tokens);
	fill_args(&tokens, &cmd_elem);
	set_level(o_parenth, c_parenth, lvl, &(cmd_elem->level));
	ft_cmds_add_back(&(all->all_cmds), cmd_elem);
	all->first_cmd = 0;
}

void	get_prev(t_cmd **cmd)
{
	t_cmd	*ptr;
	t_cmd	*hold;

	ptr = *cmd;
	if (ptr)
		ptr->prev = NULL;
	while (ptr)
	{
		hold = ptr;
		ptr = ptr->next;
		if (ptr)
			ptr->prev = hold;
	}
}

void	split_tks(t_list **tokens, t_list **tmp, t_list **cmd_start, int *sep)
{
	*sep = is_sep((*tokens)->content);
	while (*tokens && !(*sep))
	{
		*tmp = *tokens;
		*tokens = (*tokens)->next;
		if (*tokens)
			*sep = is_sep((*tokens)->content);
	}
}

void	parse_tokens(t_general *all, t_list *tokens)
{
	int		sep;
	int		lvl;
	t_list	*cmd_start;
	t_list	*tmp;

	lvl = 0;
	all->first_cmd = 1;
	while (tokens)
	{
		cmd_start = tokens;
		tmp = tokens;
		split_tks(&tokens, &tmp, &cmd_start, &sep);
		if (sep)
		{
			ft_lstdelone(tokens, free);
			tokens = tokens->next;
			tmp->next = NULL;
		}
		entitle_tokens(all, cmd_start, sep, &lvl);
	}
	get_prev(&(all->all_cmds));
}
