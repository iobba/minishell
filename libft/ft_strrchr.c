/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:35:33 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/18 20:36:55 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*last;

	last = NULL;
	str = (char *)s;
	while (*str)
	{
		if (*str == (char) c)
			last = str;
		str++;
	}
	if (*str == (char) c)
		return (str);
	return (last);
}
