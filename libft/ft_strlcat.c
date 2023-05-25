/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:17:38 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/15 17:11:36 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	if (!dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstsize < dstlen)
		return (srclen + dstsize);
	i = dstlen;
	while (src[i - dstlen] && i < dstsize - 1)
	{
		dst[i] = src[i - dstlen];
		i++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}
