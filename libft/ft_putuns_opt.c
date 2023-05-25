/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:53:23 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:11:45 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putuns_opt(t_tag tag, unsigned int nb)
{
	int	nblen;
	int	size;

	nblen = ft_nblen(nb);
	size = nblen;
	if (tag.precision > nblen)
		size = tag.precision;
	if (tag.precision == 0 && !nb)
		size--;
	if (tag.justify == ' ' || (tag.precision != -1 && tag.justify == '0'))
		size += ft_justify(' ', tag.width - size);
	if (tag.precision == -1 && tag.justify == '0')
		size += ft_justify('0', tag.width - size);
	ft_putpuns(nb, tag.precision - nblen);
	if (tag.width > size && tag.justify == '-')
		size += ft_justify(' ', tag.width - size);
	return (size);
}

void	putpuns_helper(unsigned int nb)
{
	if (nb < 10)
		ft_putchar(nb + '0');
	else
	{
		putpuns_helper(nb / 10);
		putpuns_helper(nb % 10);
	}
}

void	ft_putpuns(unsigned int nb, int plen)
{
	ft_justify('0', plen);
	if (!nb && plen == -1)
		return ;
	putpuns_helper(nb);
}
