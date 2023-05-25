/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:39:06 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:39:11 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_sep(char *s)
{
	if (!ft_strcmp(s, "||"))
		return (or_op);
	if (s[0] == '|' && !s[1])
		return (pipe_op);
	if (!ft_strcmp(s, "&&"))
		return (and_op);
	return (0);
}

int	is_redir(char *s)
{
	if (s[0] == '<' && !s[1])
		return (less);
	if (!ft_strcmp(s, "<<"))
		return (dless);
	if (s[0] == '>' && !s[1])
		return (great);
	if (!ft_strcmp(s, ">>"))
		return (dgreat);
	return (0);
}

int	is_curly(char *s)
{
	if (s[0] == '(' && !s[1])
		return (o_curly);
	if (s[0] == ')' && !s[1])
		return (c_curly);
	return (0);
}
