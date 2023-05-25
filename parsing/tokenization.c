/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:42:40 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:42:45 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_delimiter(char *s, int index)
{
	return (s[index] == ' ' || s[index] == '|'
		|| s[index] == '(' || s[index] == ')'
		|| s[index] == '<' || s[index] == '>' || s[index] == '\t'
		|| !ft_strncmp(s, "&&", 2) || !ft_strncmp(s, "||", 2));
}

char	*which_delimiter(char **s)
{
	char	*token;

	token = NULL;
	if (!ft_strncmp(*s, "||", 2))
		token = "||";
	else if (!ft_strncmp(*s, "&&", 2))
		token = "&&";
	else if (*s[0] == '|')
		token = "|";
	else if (*s[0] == '(')
		token = "(";
	else if (*s[0] == ')')
		token = ")";
	else if (!ft_strncmp(*s, "<<", 2))
		token = "<<";
	else if (!ft_strncmp(*s, ">>", 2))
		token = ">>";
	else if (*s[0] == '<')
		token = "<";
	else if (*s[0] == '>')
		token = ">";
	*s += 1;
	if (token && token[1])
		*s += 1;
	return (token);
}

int	line_tokenization(char *line, t_general *all)
{
	t_list	*tokens;
	char	*deli;
	char	*token;

	tokens = NULL;
	all->tokens = tokens;
	while (*line)
	{
		while (is_delimiter(line, 0))
		{
			deli = which_delimiter(&line);
			if (!deli)
				continue ;
			ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(deli)));
		}
		if (!(*line))
			break ;
		token = tokendup(&line);
		if (!token)
			return (ft_lstclear(&tokens, free), 1);
		ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	if (!check_syntax(tokens) || !check_extra_parenth(tokens))
		return (ft_lstclear(&tokens, free), 1);
	return (parse_tokens(all, tokens), 0);
}
