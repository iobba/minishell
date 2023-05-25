/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:16:11 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 22:09:39 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	justify(t_tag *tag, char f)
{
	if (f == '0' || f == '-')
	{
		if (f == '0' && tag->justify != '-')
			tag->justify = f;
		else
			tag->justify = '-';
	}
	else
		return (0);
	return (1);
}

int	prefix(t_tag *tag, char f)
{
	if (f == ' ' || f == '+')
	{
		if (f == ' ' && tag->prefix[0] != '+')
			tag->prefix[0] = f;
		else
			tag->prefix[0] = '+';
	}
	else if (f == '#')
		tag->prefix[1] = '#';
	else
		return (0);
	return (1);
}

int	precision(t_tag *tag, char *p)
{
	int	i;

	if (p[0] == '.')
	{
		i = 1;
		while (p[i] == '0')
			i++;
		tag->precision = ft_atoi(p + i);
		if (tag->precision)
			return (ft_nblen(tag->precision) + i);
		return (i);
	}
	return (0);
}

int	width(t_tag *tag, char *w)
{
	if (ft_isdigit(*w))
	{
		tag->width = ft_atoi(w);
		return (ft_nblen(tag->width));
	}
	return (0);
}

t_tag	formating(char *str)
{
	t_tag	tag;
	int		i;
	int		w;
	int		p;

	i = 0;
	tag.justify = ' ';
	tag.format = 0;
	tag.precision = -1;
	tag.width = 0;
	tag.prefix[0] = 0;
	tag.prefix[1] = 0;
	while (str[i] && (justify(&tag, str[i]) || prefix(&tag, str[i])))
		i++;
	w = width(&tag, &str[i]);
	if (str[i] && w)
		i += w;
	p = precision(&tag, &str[i]);
	if (str[i] && p)
		i += p;
	tag.format = str[i++];
	tag.leap = i;
	return (tag);
}
