/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:17:33 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/12 15:53:55 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct s_tag
{
	char	justify;
	char	prefix[2];
	int		precision;
	int		width;
	char	format;
	int		leap;
}t_tag;
int		ft_printf(const char *str, ...);
t_tag	formating(char *str);
int		ft_putstr_opt(t_tag tag, char *s);
int		ft_putchar_opt(t_tag tag, char c);
int		ft_putnbr_opt(t_tag tag, int nb);
int		ft_puthex_opt(t_tag tag, unsigned int nbr);
int		ft_putptr_opt(t_tag tag, unsigned long addr);
int		ft_putuns_opt(t_tag tag, unsigned int nb);
int		ft_justify(char c, int len);
int		ft_putchar(char c);
int		ft_putnstr(char *str, int len);
int		ft_strnlen(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_nblen(long nb);
int		ft_hexlen(unsigned int nb);
int		ft_ptrlen(unsigned long addr);
void	ft_putpnbr(int nbr, int plen);
void	ft_putphex(unsigned int nbr, int plen, char c);
void	ft_putptr(unsigned long addr, char *base);
void	ft_putpuns(unsigned int nb, int plen);
#endif
