/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:46:34 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:46:37 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	init_cmd_elem(t_cmd **cmd_elem, int sep)
{
	*cmd_elem = malloc(sizeof(t_cmd));
	(*cmd_elem)->cmd = NULL;
	(*cmd_elem)->args = NULL;
	(*cmd_elem)->redi_list = NULL;
	(*cmd_elem)->next = NULL;
	(*cmd_elem)->here_doc = NULL;
	(*cmd_elem)->sep = sep;
}

void	skip_parenth(t_list **tokens, int *o_parenth, int *c_parenth)
{
	int		parenth;
	t_list	*tmp;

	if (*tokens)
		parenth = is_curly((*tokens)->content);
	while (*tokens && parenth)
	{
		tmp = *tokens;
		*o_parenth += (parenth == o_curly);
		c_parenth += (parenth == c_curly);
		*tokens = (*tokens)->next;
		ft_lstdelone(tmp, free);
		if (*tokens)
			parenth = is_curly((*tokens)->content);
	}
}

void	set_level(int o_parenth, int c_parenth, int *lvl, int *cmd_lvl)
{
	if (o_parenth >= c_parenth)
	{
		o_parenth -= c_parenth;
		c_parenth = 0;
	}
	else
	{
		c_parenth -= o_parenth;
		o_parenth = 0;
	}
	*lvl += o_parenth;
	*cmd_lvl = *lvl;
	*lvl -= c_parenth;
}

void	expand_tokens(t_general *all, t_list *tokens)
{
	int	nbr_split;

	nbr_split = 0;
	while (tokens)
	{
		param_expansion(tokens, all, &nbr_split);
		while (nbr_split > 0 && tokens)
		{
			nbr_split--;
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
}

void	fill_args(t_list **tokens, t_cmd **cmd_elem)
{
	t_list	*lst;
	int		size;
	int		i;

	lst = *tokens;
	if (*tokens)
	{
		(*cmd_elem)->cmd = (*tokens)->content;
		*tokens = (*tokens)->next;
	}
	size = ft_lstsize(*tokens);
	(*cmd_elem)->args = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (*tokens)
	{
		(*cmd_elem)->args[i] = (*tokens)->content;
		i++;
		*tokens = (*tokens)->next;
	}
	(*cmd_elem)->args[i] = NULL;
	while (lst)
	{
		free(lst);
		lst = lst->next;
	}
}
