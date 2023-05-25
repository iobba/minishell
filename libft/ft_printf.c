/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:43:10 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:08:13 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_helper(t_tag tag, va_list ptr)
{
	if (tag.format == 's')
		return (ft_putstr_opt(tag, va_arg(ptr, char *)));
	else if (tag.format == 'c')
		return (ft_putchar_opt(tag, va_arg(ptr, int)));
	else if (tag.format == 'd' || tag.format == 'i')
		return (ft_putnbr_opt(tag, va_arg(ptr, int)));
	else if (tag.format == 'x' || tag.format == 'X')
		return (ft_puthex_opt(tag, va_arg(ptr, unsigned int)));
	else if (tag.format == 'p')
		return (ft_putptr_opt(tag, va_arg(ptr, unsigned long)));
	else if (tag.format == 'u')
		return (ft_putuns_opt(tag, va_arg(ptr, unsigned int)));
	else if (tag.format == '%')
		return (ft_putchar_opt(tag, '%'));
	else
		return (ft_putchar(tag.format));
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	t_tag	tag;
	int		count;

	va_start(ptr, str);
	count = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			tag = formating((char *)str + 1);
			count += ft_printf_helper(tag, ptr);
			str += tag.leap;
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(ptr);
	return (count);
}
