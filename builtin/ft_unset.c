/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:54:03 by iobba             #+#    #+#             */
/*   Updated: 2023/03/03 10:19:15 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_valid_ident(char *arg)
{
	int	i;

	if (!arg[0] || (arg[0] >= '0' && arg[0] <= '9'))
		return (1);
	i = 0;
	while (arg[i])
	{
		if ((arg[i] >= 'a' && arg[i] <= 'z')
			|| (arg[i] >= 'A' && arg[i] <= 'Z')
			|| (arg[i] >= '0' && arg[i] <= '9')
			|| arg[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

void	find_and_remove(t_env **my_env, char *arg)
{
	int		j;
	t_env	*ptr;
	t_env	*last_node;

	ptr = *my_env;
	j = 0;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, arg, ft_strlen(ptr->key) + 1))
		{
			if (!j)
				*my_env = ptr->next;
			else
				last_node->next = ptr->next;
			free(ptr->key);
			free(ptr->value);
			free(ptr);
			break ;
		}
		j++;
		last_node = ptr;
		ptr = ptr->next;
	}
}

int	ft_unset(t_env **my_env, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_valid_ident(args[i]))
			j = print_error("unset: ", args[i], ": not a valid identifier");
		else
			find_and_remove(my_env, args[i]);
		i++;
	}
	return (j);
}
