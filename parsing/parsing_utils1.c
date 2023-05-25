/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:41:34 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:41:36 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_cmds_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*head;

	if (!lst)
		return ;
	head = *lst;
	if (!head)
	{
		*lst = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}

void	ft_redi_add_back(t_io_redirect **lst, t_io_redirect *new)
{
	t_io_redirect	*head;

	if (!lst)
		return ;
	head = *lst;
	if (!head)
	{
		*lst = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*head;

	if (!lst)
		return ;
	head = *lst;
	if (!head)
	{
		*lst = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}

char	*search_value(char *token, t_expand_data *data, int i)
{
	int		len;
	char	*key;
	t_env	*env;

	env = data->all->env_list;
	key = token + *(data->ind) + 1;
	while (env)
	{
		len = ft_strlen(env->key);
		if (i == len && !ft_strncmp(env->key, key, i))
			return (env->value);
		env = env->next;
	}
	return (0);
}
