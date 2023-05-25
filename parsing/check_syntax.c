/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:38:49 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:38:58 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_parenth(t_list *tokens, t_list *prev, int curly, int *o_curly_count)
{
	if (curly == o_curly)
	{
		if (prev && is_redir(prev->content))
			return (0);
		if (prev && !is_sep(prev->content)
			&& is_curly(prev->content) != o_curly)
			return (0);
		if (tokens->next && (is_sep(tokens->next->content)
				|| is_curly(tokens->next->content) == c_curly))
			return (0);
		*o_curly_count += 1;
	}
	else if (curly == c_curly)
	{
		if (prev && (is_sep(prev->content)
				|| is_curly(prev->content) == o_curly))
			return (0);
		if (tokens->next && !is_sep(tokens->next->content)
			&& is_curly(tokens->next->content) != c_curly)
			return (0);
		if (!o_curly_count)
			return (0);
		*o_curly_count -= 1;
	}
	return (1);
}

int	check_sep_redir(t_list *tokens, t_list *prev, int *nbr_heredoc)
{
	if (is_sep(tokens->content))
	{
		if (!prev)
			return (0);
		if (!(tokens->next))
			return (0);
		if (is_sep(tokens->next->content))
			return (0);
	}
	if (is_redir(tokens->content))
	{
		*nbr_heredoc += (tokens->content[1] == '<');
		if (!(tokens->next))
			return (0);
		if (is_sep(tokens->next->content) || is_redir(tokens->next->content))
			return (0);
	}
	return (1);
}

int	check_syntax(t_list *tokens)
{
	t_list	*prev;
	int		count;
	int		curly;
	int		nbr_herdoc;

	count = 0;
	prev = NULL;
	nbr_herdoc = 0;
	while (tokens)
	{
		if (!check_parenth(tokens, prev, is_curly(tokens->content), &count))
			return (0);
		if (!check_sep_redir(tokens, prev, &nbr_herdoc))
			return (0);
		prev = tokens;
		tokens = tokens->next;
	}
	if (nbr_herdoc > 16)
	{
		ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
		exit(2);
	}
	return (!count);
}

t_list	*get_matching_parenth(t_list *tokens)
{
	int	curly;
	int	o_parenth;

	o_parenth = 1;
	while (tokens)
	{
		curly = is_curly(tokens->content);
		o_parenth += (curly == o_curly);
		if (curly == c_curly && o_parenth == 1)
			return (tokens);
		o_parenth -= (curly == c_curly);
		tokens = tokens->next;
	}
	return (NULL);
}

int	check_extra_parenth(t_list *tokens)
{
	t_list	*matching_parenth;
	t_list	*prev;

	prev = NULL;
	while (tokens)
	{
		if (is_curly(tokens->content) == o_curly)
		{
			matching_parenth = get_matching_parenth(tokens->next);
			if (prev && is_curly(prev->content) == o_curly
				&& matching_parenth->next
				&& is_curly(matching_parenth->next->content) == c_curly)
				return (0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}
