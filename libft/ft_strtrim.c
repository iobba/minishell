/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:29:07 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/18 21:06:26 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	search(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end	;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && search(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && search(s1[end], set))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
