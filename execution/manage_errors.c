/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:28:55 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:48:03 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	error_exit(char *str)
{
	perror(str);
	exit (errno);
}

int	print_error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int	error_errno(char *str)
{
	perror(str);
	return (errno);
}

void	no_cmd_file(char **arg, char *str)
{
	write(2, "minishell: ", 11);
	write(2, arg[0], ft_strlen(arg[0]));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(arg);
	exit (127);
}

void	error_execve(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd);
	exit (126);
}
