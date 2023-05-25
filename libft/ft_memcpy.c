/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:25:01 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/13 20:27:01 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	if (!src && !dst)
		return (NULL);
	i = 0;
	s1 = dst;
	s2 = (void *) src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}
