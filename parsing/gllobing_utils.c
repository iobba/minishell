/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gllobing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:39:48 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:39:52 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_index(char *token)
{
	int		i;
	char	quote;

	i = -1;
	while (token[++i])
	{
		quote = token[i];
		if (quote == '\"' || quote == '\'')
		{
			i++;
			while (token[i] != quote)
				i++;
		}
		else
			if (token[i] == '*')
				return (i);
	}
	return (-1);
}

void	get_last_index(char *token, int *ind)
{
	int	tmp;

	tmp = get_index(token + *ind + 1);
	while (tmp >= 0)
	{
		*ind += tmp + 1;
		tmp = get_index(token + *ind + 1);
	}
}

int	begin_match(char **haystack, char *needle, int ind)
{
	char	quote;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < ind)
	{
		quote = needle[i];
		if (quote == '\"' || quote == '\'')
		{
			while (needle[++i] != quote)
			{
				if (needle[i] != (*haystack)[j])
					return (0);
				j++;
			}
		}
		else
			if ((*haystack)[j++] != needle[i])
				return (0);
	}
	*haystack += ind;
	return (1);
}

int	tail_match(char *haystack, char *needle, int ind)
{
	char	quote;
	int		i;
	int		j;

	i = ft_strlen(needle);
	j = ft_strlen(haystack) - 1;
	while (--i > ind)
	{
		quote = needle[i];
		if (quote == '\"' || quote == '\'')
		{
			i--;
			while (i > end && needle[i] != quote)
			{
				if (j < 0 || haystack[j--] != needle[i])
					return (0);
				i--;
			}
		}
		else
			if (j < 0 || haystack[j--] != needle[i])
				return (0);
	}
	return (1);
}

char	*sub_match(char **haystack, char *needle, int ref, int len)
{
	char	*sub;
	int		nbr_quotes;
	char	*match_occu;
	int		i;
	char	quote;

	sub = ft_substr(needle, ref + 1, len);
	nbr_quotes = count_quotes(sub);
	if (nbr_quotes)
		sub = remove_quotes(sub, nbr_quotes);
	match_occu = ft_strnstr(*haystack, sub, ft_strlen(*haystack));
	free(sub);
	if (match_occu)
				*haystack = match_occu + len - nbr_quotes;
	return (match_occu);
}
