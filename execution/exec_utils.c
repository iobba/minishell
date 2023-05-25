/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:35:57 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:41:50 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	size_of_env(t_env *my_env)
{
	t_env	*ptr;
	int		size;

	size = 0;
	ptr = my_env;
	while (ptr)
	{
		if (ptr->is_printed)
			size++;
		ptr = ptr->next;
	}
	return (size);
}

char	**env_arr(t_env *my_env)
{
	t_env	*ptr;
	int		size;
	char	**env;
	char	*hold;

	size = size_of_env(my_env);
	env = malloc(++size * sizeof(char *));
	if (!env)
		error_exit("minishell");
	ptr = my_env;
	size = 0;
	while (ptr)
	{
		if (ptr->is_printed)
		{
			hold = ft_strjoin(ptr->key, "=");
			env[size++] = ft_strjoin(hold, ptr->value);
			free (hold);
		}
		ptr = ptr->next;
	}
	env[size] = NULL;
	return (env);
}

void	freeing(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	is_dots(char *cmd, int print_msg)
{
	if (!ft_strncmp(cmd, "..", 3))
	{
		if (print_msg)
			ft_putendl_fd("minishell: ..: command not found", 2);
		return (127);
	}
	if (!ft_strncmp(cmd, ".", 2))
	{
		if (print_msg)
		{
			ft_putendl_fd("minishell: .: filename argument required", 2);
			ft_putendl_fd(".: usage: . filename [arguments]", 2);
		}
		return (2);
	}
	return (0);
}

int	is_dir(const char *path)
{
	DIR	*dir_ptr;

	dir_ptr = opendir(path);
	if (dir_ptr)
	{
		closedir(dir_ptr);
		print_error("minishell: ", (char *)path, ": is a directory");
		return (1);
	}
	return (0);
}
