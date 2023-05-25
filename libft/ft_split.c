/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:01:50 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/19 17:51:59 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*dupl(char const **str, char c)
{
	char	*s;
	int		i;
	int		size;

	size = len(*str, c);
	s = malloc(size + 1);
	if (!s)
		return (s);
	i = 0;
	while (i < size)
	{
		s[i] = *(*str);
		i++;
		(*str)++;
	}
	s[i] = '\0';
	return (s);
}

static char	**ft_clear_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*word;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	arr = malloc (sizeof(char *) * (size + 1));
	if (!arr)
		return (arr);
	i = 0;
	while (i < size)
	{
		while (*s == c)
			s++;
		word = dupl(&s, c);
		if (!word)
			return (ft_clear_tab(arr, i));
		arr[i++] = word;
	}
	arr[i] = NULL;
	return (arr);
}
