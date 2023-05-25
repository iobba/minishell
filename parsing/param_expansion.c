/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:41:07 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/10 12:37:27 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	handle_last_exit(char **token, char *sub, t_expand_data *data)
{
	char	*tmp;
	char	*last_exit_str;

	if (data->all->first_cmd)
		last_exit_str = ft_itoa(g_last_exit);
	else
		last_exit_str = ft_strdup("0");
	sub = ft_strjoin_free(sub, last_exit_str);
	tmp = ft_strjoin(sub, *token + *(data->ind) + 2);
	*(data->ind) += ft_strlen(last_exit_str) - 1;
	free(sub);
	free(*token);
	*token = tmp;
}

int	handle_variable(char **token, char *sub, char *value, int i)
{
	int		step;
	char	*tmp;

	if (value)
	{
		step = ft_strlen(value);
		value = ft_strjoin(value, *token + i);
		free(*token);
		*token = ft_strjoin_free(sub, value);
		return (step);
	}
	step = 0;
	tmp = ft_strjoin(sub, *token + i);
	free(sub);
	free(*token);
	*token = tmp;
	return (0);
}

void	variable_substitution(t_expand_data *data)
{
	char	**token;
	char	*sub;
	char	*value;
	int		i;

	token = &((*(data->tokens))->content);
	sub = ft_substr(*token, 0, *(data->ind));
	i = *(data->ind) + 1;
	while (ft_isalnum((*token)[i]) || (*token)[i] == '_')
		i++;
	if (!(i - *(data->ind) - 1))
	{
		if ((*token)[i] == '?')
			handle_last_exit(token, sub, data);
		else if ((*(data->ind))++)
			free(sub);
		return ;
	}
	value = search_value(*token, data, i - *(data->ind) - 1);
	if (value && data->to_split)
	{
		*(data->ind) += handle_split(sub, value, i, data);
		return ;
	}
	*(data->ind) += handle_variable(token, sub, value, i);
}

void	handle_quotes(t_expand_data *data)
{
	char	**token;
	char	quote;

	token = &((*(data->tokens))->content);
	quote = (*token)[*(data->ind)];
	*(data->ind) += 1;
	while ((*token)[*(data->ind)] && (*token)[*(data->ind)] != quote)
	{
		if (quote == '\"' && (*token)[*(data->ind)] == '$')
		{
			data->to_split = 0;
			variable_substitution(data);
			continue ;
		}
		*(data->ind) += 1;
	}
	*(data->ind) += 1;
}

void	param_expansion(t_list *tokens, t_general *all, int *nbr_split)
{
	t_expand_data	data;
	int				i;

	data.tokens = &tokens;
	data.all = all;
	data.ind = &i;
	data.nbr_split = nbr_split;
	data.to_split = 1;
	i = 0;
	*nbr_split = 0;
	while ((tokens->content)[i])
	{
		if ((tokens->content)[i] == '\"' || (tokens->content)[i] == '\'')
			handle_quotes(&data);
		else if ((tokens->content)[i] == '$')
			variable_substitution(&data);
		else if ((tokens->content)[i])
			i++;
	}
}
