/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:53:55 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/15 17:10:04 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			i;
	size_t			n;

	n = count * size;
	if (count && size >= SIZE_MAX / count)
		return (NULL);
	mem = malloc(n);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < n)
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
