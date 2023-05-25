/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:41:49 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:41:51 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*remove_quotes(char *token, int quotes_nbr)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (ft_strlen(token) - quotes_nbr + 1));
	if (!new)
		error_exit("2ishell");
	i = -1;
	j = 0;
	while (token[++i])
	{
		quote = token[i];
		if (token[i] == '\"' || token[i] == '\'')
		{
			while (token[++i] != quote)
				new[j++] = token[i];
		}
		else
			new[j++] = token[i];
	}
	new[j] = '\0';
	free(token);
	return (new);
}

int	count_quotes(char *s)
{
	int		nbr_quotes;
	char	quote;

	nbr_quotes = 0;
	while (*s)
	{
		quote = *s;
		if (quote == '\"' || quote == '\'')
		{
			nbr_quotes += 2;
			s++;
			while (*s != quote)
				s++;
		}
		s++;
	}
	return (nbr_quotes);
}
