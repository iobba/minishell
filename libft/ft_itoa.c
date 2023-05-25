/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:49:19 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/15 16:13:01 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	helper(char *str, long nbr, int size)
{
	if (!nbr)
	{
		*str = '0';
		return ;
	}
	while (nbr)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;
	int		size;

	size = 0;
	nbr = n;
	if (n < 0)
	{
		nbr *= -1;
		size++;
	}
	size += count_digits(nbr);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	if (n < 0)
		*str = '-';
	str[size--] = '\0';
	helper(str, nbr, size);
	return (str);
}
