/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gllobing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:39:39 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/09 17:39:42 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	insert_tokens(t_list **tokens, char *match)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = ft_strdup(match);
	new->next = (*tokens)->next;
	(*tokens)->next = new;
	*tokens = (*tokens)->next;
}

int	check_match(char *haystack, char *needle)
{
	int		ind;
	int		match;
	int		ref;
	int		len;

	ind = get_index(needle);
	ref = ind;
	match = begin_match(&haystack, needle, ind);
	get_last_index(needle, &ind);
	while (ref < ind)
	{
		len = get_index(needle + ref + 1);
		if (len > 0 && len < ind - ref)
			if (!sub_match(&haystack, needle, ref, len) && match)
				match = !match;
		ref += len;
		if (ref < ind)
			ref++;
	}
	return (match && tail_match(haystack, needle, ind));
}

int	get_matchs(DIR *dir, t_list *tokens, char *needle, int *first)
{
	struct dirent	*entry;
	int				nbr_matchs;

	nbr_matchs = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (check_match(entry->d_name, needle))
		{
			if (first)
				tokens->content = ft_strdup(entry->d_name);
			else
				insert_tokens(&tokens, entry->d_name);
			first = 0;
			nbr_matchs += 1;
		}
		entry = readdir(dir);
	}
	return (nbr_matchs);
}

void	filename_expand(t_list *tokens, int nbr_quotes, int *nbr_matchs)
{
	DIR				*dir;
	struct dirent	*entry;
	int				first;
	char			*needle;

	dir = opendir(".");
	if (!dir)
		return ;
	first = 1;
	needle = tokens->content;
	*nbr_matchs += get_matchs(dir, tokens, needle, &first);
	closedir(dir);
	if (first)
		tokens->content = remove_quotes(tokens->content, nbr_quotes);
	else
		free(needle);
}

int	gllobing(t_list *tokens, int *nbr_matchs)
{
	int		ind;
	int		quotes_nbr;
	char	*token;

	quotes_nbr = 0;
	*nbr_matchs = 0;
	ind = get_index(tokens->content);
	quotes_nbr = count_quotes(tokens->content);
	if (ind >= 0)
		filename_expand(tokens, quotes_nbr, nbr_matchs);
	return (ind >= 0);
}
