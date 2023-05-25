/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:46:55 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:09:54 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_opt(t_tag tag, int nb)
{
	int	nblen;
	int	size;

	nblen = ft_nblen(nb);
	size = nblen;
	if (tag.precision > nblen)
		size = tag.precision;
	if (tag.precision == 0 && !nb)
		size--;
	if (nb < 0 || tag.prefix[0])
		size++;
	if (tag.justify == ' ' || (tag.precision != -1 && tag.justify == '0'))
		size += ft_justify(' ', tag.width - size);
	if (nb < 0)
		ft_putchar('-');
	if (nb >= 0 && tag.prefix[0])
		ft_putchar(tag.prefix[0]);
	if (tag.precision == -1 && tag.justify == '0')
		size += ft_justify('0', tag.width - size);
	ft_putpnbr(nb, tag.precision - nblen);
	if (tag.width > size && tag.justify == '-')
		size += ft_justify(' ', tag.width - size);
	return (size);
}

void	putpnbr_helper(int nbr)
{
	if (nbr == -2147483648)
		ft_putnstr("2147483648", 10);
	else if (nbr < 0)
		putpnbr_helper(-nbr);
	else if (nbr < 10)
		ft_putchar(nbr + '0');
	else
	{
		putpnbr_helper(nbr / 10);
		putpnbr_helper(nbr % 10);
	}
}

void	ft_putpnbr(int nbr, int plen)
{
	ft_justify('0', plen);
	if (!nbr && plen == -1)
		return ;
	putpnbr_helper(nbr);
}

int	ft_nblen(long nb)
{
	int	nblen;

	nblen = 0;
	if (nb < 0)
		return (ft_nblen(-nb));
	if (nb < 10)
		return (1);
	while (nb)
	{
		nblen++;
		nb /= 10;
	}
	return (nblen);
}
