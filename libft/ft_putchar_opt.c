/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:52:43 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:10:45 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_opt(t_tag tag, char c)
{
	int	count;

	count = 0;
	if (tag.justify != '-')
		count += ft_justify(' ', tag.width - 1);
	count += ft_putchar(c);
	if (tag.justify == '-')
		count += ft_justify(' ', tag.width - 1);
	return (count);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
