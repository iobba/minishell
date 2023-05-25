/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokendup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:42:00 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:42:03 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*tokendup(char **line)
{
	char	*s;

	s = *line;
	if (*s == '\"' || *s == '\'')
		return (tokendup_dquote(line, *s));
	else if (*s)
		return (tokendup_simple(line));
	else
		return (ft_strdup(""));
}

char	*tokendup_dquote(char **line, char c)
{
	int		i;
	char	*s;
	char	*dup;

	s = *line;
	i = 1;
	while (s[i] && s[i] != c)
		i++;
	*line += i + 1;
	if (s[i] == c)
	{
		dup = ft_substr(s, 0, i + 1);
		if (!dup)
			return (NULL);
		if (is_delimiter(*line, 0))
			return (dup);
		return (ft_strjoin_free(dup, tokendup(line)));
	}
	return (NULL);
}

char	*tokendup_simple(char **line)
{
	int		i;
	char	*s;
	char	*dup;

	s = *line;
	i = 0;
	while (s[i] && s[i] != '\"' && s[i] != '\'' && !is_delimiter(s, i))
		i++;
	*line += i;
	dup = ft_substr(s, 0, i);
	if (is_delimiter(s, i))
		return (dup);
	return (ft_strjoin_free(dup, tokendup(line)));
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}
