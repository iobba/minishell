/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:00:58 by iobba             #+#    #+#             */
/*   Updated: 2023/03/08 15:58:53 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	update_oldpwd(char *n_oldpwd, t_env **my_env)
{
	t_env	*ptr;

	ptr = *my_env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, "OLDPWD", 7))
		{
			free(ptr->value);
			ptr->value = malloc((ft_strlen(n_oldpwd) + 1) * sizeof(char));
			if (!ptr->value)
				error_exit("allocation");
			ft_strlcpy(ptr->value, n_oldpwd, ft_strlen(n_oldpwd) + 1);
			return ;
		}
		ptr = ptr->next;
	}
}

int	change_dir(char *path, t_env **my_env)
{
	int		i;
	t_env	*ptr;

	i = chdir(path);
	if (i)
		return (error_errno(path), 1);
	path = getcwd(NULL, 0);
	if (!path)
		return (error_errno("getcwd"));
	ptr = *my_env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, "PWD", 4))
		{
			update_oldpwd(ptr->value, my_env);
			free(ptr->value);
			ptr->value = malloc((ft_strlen(path) + 1) * sizeof(char));
			if (!ptr->value)
				error_exit("allocation");
			ft_strlcpy(ptr->value, path, ft_strlen(path) + 1);
			return (free(path), EXIT_SUCCESS);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

int	get_home_back(t_env **my_env, int i)
{
	t_env	*ptr;

	ptr = *my_env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, "HOME", 5) && i == 0)
		{
			if (!ptr->value[0])
				return (EXIT_SUCCESS);
			return (change_dir(ptr->value, my_env));
		}
		if (!ft_strncmp(ptr->key, "OLDPWD", 7) && i)
		{
			ft_putstr_fd(ptr->value, i);
			ft_putchar_fd('\n', i);
			return (change_dir(ptr->value, my_env));
		}
		ptr = ptr->next;
	}
	if (i)
		return (print_error("minishell: cd: OLDPWD not set", "", ""));
	else
		return (print_error("minishell: cd: HOME not set", "", ""));
	return (EXIT_SUCCESS);
}

int	ft_cd(char **args, t_env **my_env, int fd_out)
{
	t_env	*ptr;

	ptr = *my_env;
	if (!args[0])
		return (get_home_back(my_env, 0));
	if (!ft_strncmp(args[0], "-", 2))
		return (get_home_back(my_env, fd_out));
	return (change_dir(args[0], my_env));
}
