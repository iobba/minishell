/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:41:16 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:41:19 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	insert_tokens(t_list *tokens, char *match)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = match;
	new->next = tokens->next;
	tokens->next = new;
	return (1);
}

int	first_split(char *sub, char *value, char *next, t_expand_data *data)
{
	t_list	**tokens;
	char	*tmp;
	int		len;

	len = ft_strlen(data->arr);
	tokens = data->tokens;
	if (value[0] != ' ' || !sub[0])
		(*tokens)->content = ft_strjoin_free(sub, data->arr);
	else
	{
		(*tokens)->content = sub;
		*(data->nbr_split) += insert_tokens(*tokens, data->arr);
		*tokens = (*tokens)->next;
	}
	if (!data->arr_next && next[0])
	{
		tmp = (*tokens)->content;
		(*tokens)->content = ft_strjoin((*tokens)->content, next);
		free(tmp);
	}
	return (len);
}

int	next_split(char *value, char *next, t_expand_data *data)
{
	t_list	**tokens;
	int		ind;

	ind = 0;
	tokens = data->tokens;
	*(data->nbr_split) += insert_tokens(*tokens, data->arr);
	*tokens = (*tokens)->next;
	if (!data->arr_next)
	{
		if (value[ft_strlen(value) - 1] != ' ')
		{
			(*tokens)->content = ft_strjoin((*tokens)->content, next);
			free(data->arr);
			ind = ft_strlen(data->arr);
		}
		else if (*next)
			*(data->nbr_split) += insert_tokens(*tokens, ft_strdup(next));
	}
	return (ind);
}

int	handle_split(char *sub, char *value, int i, t_expand_data *data)
{
	char	**arr;
	char	*token;
	int		first;
	int		j;
	int		ind;

	token = (*(data->tokens))->content;
	arr = ft_split(value, ' ');
	first = 1;
	j = -1;
	ind = 0;
	if (!arr[0])
		return (*(data->nbr_split) = -1, free(arr[0]), free(arr),
			handle_variable(&((*(data->tokens))->content), sub, "", i));
	while (arr[++j])
	{
		data->arr = arr[j];
		data->arr_next = arr[j + 1];
		if (first && !(--first))
			ind = first_split(sub, value, token + i, data);
		else
			ind = next_split(value, token + i, data);
	}
	return (free(arr[j]), free(arr), free(token), ind);
}
