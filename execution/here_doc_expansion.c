/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:00:23 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:36:07 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*is_key(char *key, t_env *env, int i)
{
	int	len;

	while (env)
	{
		len = ft_strlen(env->key);
		if (i == len && !ft_strncmp(env->key, key, i))
			return (env->value);
		env = env->next;
	}
	return (0);
}

void	get_last_exit(char **line, char *sub, int *ind)
{
	char	*tmp;
	char	*last_exit_str;

	last_exit_str = ft_itoa(g_last_exit);
	sub = ft_strjoin_free(sub, last_exit_str);
	tmp = ft_strjoin(sub, (*line) + *ind + 2);
	*ind += ft_strlen(last_exit_str) - 1;
	free(sub);
	free((*line));
	(*line) = tmp;
}

int	add_value(char **line, char *sub, char *value, int i)
{
	int		step;
	char	*tmp;

	if (value)
	{
		step = ft_strlen(value);
		value = ft_strjoin(value, (*line) + i);
		free((*line));
		(*line) = ft_strjoin_free(sub, value);
		return (step);
	}
	step = 0;
	tmp = ft_strjoin(sub, (*line) + i);
	free(sub);
	free((*line));
	(*line) = tmp;
	return (0);
}

void	get_key_size(char **line, t_general *all, int *ind)
{
	char	*sub;
	char	*value;
	int		i;

	sub = ft_substr((*line), 0, *ind);
	i = *ind + 1;
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	if (!(i - *ind - 1))
	{
		if ((*line)[i] == '?')
			get_last_exit(line, sub, ind);
		else
			*ind += 1;
		return ;
	}
	value = is_key((*line) + *ind + 1, all->env_list, i - *ind - 1);
	*ind += add_value(line, sub, value, i);
}

void	here_doc_expansion(char **line, t_general *all)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			get_key_size(line, all, &i);
		else if ((*line)[i])
			i++;
	}
}
