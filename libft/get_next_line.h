/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:27:11 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/13 21:52:10 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_indexof(char *buffer);
char	*subbuffer(char *s1, int start, int len);
char	*bufferjoin(char *s1, char *s2);
int		ft_strlen(const char *s);
char	*fetch_line(char **left, int ind);
char	*fetch_remainder(char **left);
#endif
