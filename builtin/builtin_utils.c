/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:16:14 by iobba             #+#    #+#             */
/*   Updated: 2023/03/08 10:42:22 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_one_var(t_env *ptr, int fd_out)
{
	ft_putstr_fd("declare -x ", fd_out);
	ft_putstr_fd(ptr->key, fd_out);
	if (ptr->is_printed)
	{
		ft_putchar_fd('=', fd_out);
		ft_putchar_fd('\"', fd_out);
		ft_putstr_fd(ptr->value, fd_out);
		ft_putchar_fd('\"', fd_out);
	}
	ft_putchar_fd('\n', fd_out);
}

t_env	*get_smallest(t_env *env, char *last_small)
{
	t_env	*ptr;
	t_env	*smallest;
	t_env	*biggest;

	ptr = env;
	biggest = ptr;
	while (ptr)
	{
		if (ft_strcmp(biggest->key, ptr->key) < 0)
			biggest = ptr;
		ptr = ptr->next;
	}
	if (last_small && !ft_strcmp(biggest->key, last_small))
		return (NULL);
	ptr = env;
	smallest = biggest;
	while (ptr)
	{
		if (ft_strcmp(smallest->key, ptr->key) > 0
			&& (last_small == NULL || ft_strcmp(ptr->key, last_small) > 0))
			smallest = ptr;
		ptr = ptr->next;
	}
	return (smallest);
}

void	sort_and_show_vars(t_env *my_env, int fd_out)
{
	t_env	*ptr;
	t_env	*smallest;

	ptr = my_env;
	smallest = get_smallest(my_env, NULL);
	while (1)
	{
		print_one_var(smallest, fd_out);
		smallest = get_smallest(my_env, smallest->key);
		if (!smallest)
			return ;
	}
}
