/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:03:49 by iobba             #+#    #+#             */
/*   Updated: 2023/03/08 13:41:54 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_key(char *arg, t_env **my_env)
{
	t_env	*ptr;
	int		i;
	char	*new;

	ptr = *my_env;
	new = get_key(arg);
	i = ft_strlen(new);
	while (ptr)
	{
		if (!ft_strncmp(new, ptr->key, i + 1) && arg[i] != '\0')
			return (free(new), 1);
		if (!ft_strncmp(new, ptr->key, i + 1) && arg[i] == '\0')
			return (free(new), 2);
		ptr = ptr->next;
	}
	if (arg[i] != '\0')
		return (free(new), 3);
	return (free(new), 4);
}

void	ft_update_value(char *arg, t_env **my_env, int append)
{
	t_env	*ptr;
	int		i;
	char	*new;

	new = get_key(arg);
	i = ft_strlen(new);
	ptr = *my_env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, new, i + 1))
		{
			ptr->is_printed = 1;
			if (append == 2)
				ptr->value = ft_strjoin_free(ptr->value, get_var_value(arg));
			else
			{
				free(ptr->value);
				ptr->value = get_var_value(arg);
			}
			free(new);
			return ;
		}
		ptr = ptr->next;
	}
	free(new);
}

void	ft_add_var(char *arg, t_env **my_env, int n)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		error_exit("allocation");
	new_var->key = get_key(arg);
	new_var->value = get_var_value(arg);
	new_var->next = NULL;
	new_var->is_printed = n;
	ft_env_add_back(my_env, new_var);
}

int	is_valid(char *arg)
{
	int	i;

	if (!arg[0] || (arg[0] >= '0' && arg[0] <= '9')
		|| arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i && arg[i] == '+' && arg[i + 1] == '=')
			return (2);
		else if ((arg[i] >= 'a' && arg[i] <= 'z')
			|| (arg[i] >= 'A' && arg[i] <= 'Z')
			|| (arg[i] >= '0' && arg[i] <= '9')
			|| arg[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_export(char **args, t_env **my_env, int fd_out)
{
	int	i;
	int	check;
	int	j;

	i = 0;
	j = 0;
	if (!args[0] && *my_env)
		sort_and_show_vars(*my_env, fd_out);
	while (args[i])
	{
		if (!is_valid(args[i]))
			j = print_error("export: ", args[i], ": not a valid identifier");
		else
		{
			check = check_key(args[i], my_env);
			if (check == 1)
				ft_update_value(args[i], my_env, is_valid(args[i]));
			if (check == 3)
				ft_add_var(args[i], my_env, 1);
			if (check == 4)
				ft_add_var(args[i], my_env, 0);
		}
		i++;
	}
	return (j);
}
