/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:47:44 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:10:23 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_opt(t_tag tag, char *s)
{
	int	len;
	int	size;

	len = ft_strnlen(s);
	if (tag.precision >= 0 && tag.precision < len)
		len = tag.precision;
	size = len;
	if (tag.width > size)
		size = tag.width;
	if (tag.justify != '-')
		ft_justify(tag.justify, size - len);
	ft_putnstr(s, len);
	if (tag.justify == '-')
		ft_justify(' ', size - len);
	return (size);
}

int	ft_putnstr(char *str, int len)
{
	if (!str)
		return (write(1, "(null)", len));
	return (write(1, str, len));
}

int	ft_strnlen(char *str)
{
	int	i;

	if (!str)
		return (6);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
