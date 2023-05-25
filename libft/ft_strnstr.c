/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:47:12 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/15 16:02:22 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	i;
	size_t	k;

	if (!needle[0])
		return ((char *) haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		k = i;
		while (needle[j] && k < len)
		{
			if (haystack[k] != needle[j])
				break ;
			j++;
			k++;
		}
		if (!needle[j])
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}
