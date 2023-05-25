/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:50:23 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:11:07 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_opt(t_tag tag, unsigned int nbr)
{
	int	size;
	int	hexlen;

	hexlen = ft_hexlen(nbr);
	size = hexlen;
	if (tag.precision > size)
		size = tag.precision;
	if (tag.precision == 0 && !nbr)
		size--;
	if (tag.prefix[1] && nbr)
		size += 2;
	if (tag.justify == ' ' || (tag.precision != -1 && tag.justify == '0'))
		size += ft_justify(' ', tag.width - size);
	if (tag.prefix[1] && nbr)
	{
		ft_putchar('0');
		ft_putchar(tag.format);
	}
	if (tag.justify == '0' && tag.precision == -1)
		size += ft_justify('0', tag.width - size);
	ft_putphex(nbr, tag.precision - hexlen, tag.format);
	if (tag.justify == '-')
		size += ft_justify(' ', tag.width - size);
	return (size);
}

void	putphex_helper(unsigned int nbr, char *base)
{
	if (nbr < 16)
	{
		ft_putchar(base[nbr]);
		return ;
	}
	putphex_helper(nbr / 16, base);
	putphex_helper(nbr % 16, base);
}

void	ft_putphex(unsigned int nbr, int plen, char c)
{
	char	*base;

	if (!nbr && plen == -1)
		return ;
	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	ft_justify('0', plen);
	putphex_helper(nbr, base);
}

int	ft_hexlen(unsigned int nb)
{
	int	hexlen;

	hexlen = 0;
	if (nb < 16)
		return (1);
	while (nb)
	{
		hexlen++;
		nb /= 16;
	}
	return (hexlen);
}
