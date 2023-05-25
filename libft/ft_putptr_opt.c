/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:51:43 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:11:24 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_opt(t_tag tag, unsigned long addr)
{
	int	ptrlen;
	int	size;

	ptrlen = ft_ptrlen(addr);
	size = ptrlen;
	if (tag.precision > size)
		size = tag.precision;
	size += 2;
	if (tag.justify == ' ')
		size += ft_justify(' ', tag.width - size);
	ft_putnstr("0x", 2);
	if (tag.justify == '0' && tag.precision == -1)
		size += ft_justify('0', tag.width - size);
	ft_justify('0', tag.precision - ptrlen);
	ft_putptr(addr, "0123456789abcdef");
	if (tag.justify == '-')
		size += ft_justify(' ', tag.width - size);
	return (size);
}

void	ft_putptr(unsigned long addr, char *base)
{
	if (addr < 16)
	{
		ft_putchar(base[addr]);
		return ;
	}
	ft_putptr(addr / 16, base);
	ft_putptr(addr % 16, base);
}

int	ft_ptrlen(unsigned long addr)
{
	int	ptrlen;

	ptrlen = 0;
	if (addr < 16)
		return (1);
	while (addr)
	{
		ptrlen++;
		addr /= 16;
	}
	return (ptrlen);
}
