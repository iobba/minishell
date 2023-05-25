/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:53:54 by iobba             #+#    #+#             */
/*   Updated: 2023/03/03 10:10:52 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	found_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] != '\0')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, int fd_out)
{
	int	i;
	int	put_new_line;
	int	non_new_line;

	put_new_line = 1;
	non_new_line = 0;
	i = 0;
	while (args[i] && found_n(args[i]))
	{
		put_new_line = 0;
		i += 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1])
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (put_new_line)
		ft_putchar_fd('\n', fd_out);
	return (EXIT_SUCCESS);
}
