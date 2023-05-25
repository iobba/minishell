/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:28:57 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 21:52:34 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line_helper(int fd, char *buffer)
{
	static char	*left;
	int			n;
	int			ind;

	n = read(fd, buffer, BUFFER_SIZE);
	if (!left)
		left = subbuffer("", 0, 0);
	while (n >= 0)
	{
		buffer[n] = '\0';
		left = bufferjoin(left, buffer);
		ind = ft_indexof(left);
		if (ind != -1)
			return (fetch_line(&left, ind));
		if (!n && left[0] != '\0')
			return (fetch_remainder(&left));
		if (!n)
			break ;
		n = read(fd, buffer, BUFFER_SIZE);
	}
	free(left);
	left = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = get_next_line_helper(fd, buffer);
	free(buffer);
	return (line);
}

char	*fetch_line(char **left, int ind)
{
	char	*line;
	char	*tmp;

	line = subbuffer(*left, 0, ind + 1);
	tmp = subbuffer(*left, ind + 1, ft_strlen(*left) - ind);
	free(*left);
	*left = tmp;
	return (line);
}

char	*fetch_remainder(char **left)
{
	char	*line;

	line = subbuffer(*left, 0, ft_strlen(*left) + 1);
	free(*left);
	*left = NULL;
	return (line);
}
