/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:09:02 by iobba             #+#    #+#             */
/*   Updated: 2023/03/05 13:38:50 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_var_value(char *env_line)
{
	int		i;
	char	*value;
	int		size;

	i = 0;
	while (env_line[i] != '=' && env_line[i])
		i++;
	size = ft_strlen(env_line) - i;
	value = malloc(size * sizeof(char));
	if (!value)
		error_exit("allocation");
	ft_strlcpy(value, env_line + i + 1, size);
	return (value);
}

char	*get_key(char *env_line)
{
	int		i;
	char	*key;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '+' && env_line[i])
		i++;
	key = malloc((i + 1) * sizeof(char));
	if (!key)
		error_exit("allocation");
	ft_strlcpy(key, env_line, i + 1);
	return (key);
}

void	ft_setenv(t_env **my_env, char **env)
{
	t_env	*env_var;
	int		i;

	*my_env = NULL;
	i = 0;
	while (env[i])
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			error_exit("allocation");
		env_var->key = get_key(env[i]);
		env_var->value = get_var_value(env[i]);
		env_var->next = NULL;
		env_var->is_printed = 1;
		ft_env_add_back(my_env, env_var);
		i++;
	}
}

int	found_path(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, "PATH", 4))
			return (EXIT_SUCCESS);
		ptr = ptr->next;
	}
	return (EXIT_FAILURE);
}

int	ft_env(t_env *env, int fd_out)
{
	t_env	*ptr;

	if (found_path(env))
	{
		print_error("minishell: ", "env: ", "No such file or directory");
		return (127);
	}
	ptr = env;
	while (ptr)
	{
		if (ptr->is_printed)
		{
			ft_putstr_fd(ptr->key, fd_out);
			ft_putchar_fd('=', fd_out);
			ft_putstr_fd(ptr->value, fd_out);
			ft_putchar_fd('\n', fd_out);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
