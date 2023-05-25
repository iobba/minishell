/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:29:19 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/07 15:21:01 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_err(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

static int	f_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	check_min(char *str)
{
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (1);
	return (0);
}

int	ft_atoi(char *s)
{
	int					i;
	unsigned long		result;
	int					sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		sign = f_sign(s[i]);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - 48;
		if (check_min(s))
			return (0);
		else if ((result > 9223372036854775807 && sign == 1)
			|| (result > 9223372036854775807 && sign == -1))
			return (put_err("exit: ", s, ": numeric argument required"), 255);
		i++;
	}
	return (((int)result) * sign);
}
