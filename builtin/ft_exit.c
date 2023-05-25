/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:28:18 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 11:54:54 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_numeric(char *nb)
{
	int	i;
	int	found_nbr;

	i = 0;
	found_nbr = 0;
	while (nb[i] == ' ')
		i++;
	if ((nb[i] == '-' || nb[i] == '+') && nb[i + 1])
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		found_nbr++;
		i++;
	}
	while (nb[i] == ' ')
		i++;
	if (!found_nbr || !i || nb[i])
		return (0);
	return (1);
}

int	ft_exit(char **arg, int is_print)
{
	int	i;

	i = 0;
	if (arg[0] && !ft_strncmp(arg[0], "--", 3))
		i++;
	if (is_print)
		write(2, "exit\n", 5);
	if (arg[i])
	{
		if (is_numeric(arg[i]))
		{
			if (arg[i + 1])
			{
				write(2, "minishell: exit: too many arguments\n", 36);
				return (EXIT_FAILURE);
			}
			exit(ft_atoi(arg[i]));
		}
		print_error("minishell: exit: ", arg[i], ": numeric argument required");
		exit(255);
	}
	else
		exit (g_last_exit);
	return (EXIT_FAILURE);
}
