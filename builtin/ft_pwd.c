/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:00:18 by iobba             #+#    #+#             */
/*   Updated: 2023/03/05 15:32:20 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_pwd(int fd_out)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (error_errno("getcwd"));
	ft_putstr_fd(cur_dir, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(cur_dir);
	return (EXIT_SUCCESS);
}
