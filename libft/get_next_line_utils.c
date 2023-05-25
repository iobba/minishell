/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:59:14 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:42:09 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_indexof(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*subbuffer(char *s1, int start, int len)
{
	char	*ans;
	int		i;

	ans = malloc(len + 1);
	if (!ans)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ans[i] = s1[start + i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	*bufferjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		s[i] = s2[j];
		j++;
		i++;
	}
	s[i] = '\0';
	free(s1);
	s1 = NULL;
	return (s);
}
