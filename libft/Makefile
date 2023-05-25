# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalhi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 21:19:36 by isalhi            #+#    #+#              #
#    Updated: 2022/11/13 22:32:36 by isalhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strchr.c \
	   ft_strrchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strncmp.c ft_strcmp.c\
	   ft_strlcpy.c ft_strlen.c ft_strlcat.c ft_isalpha.c ft_isdigit.c \
	   ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	   ft_calloc.c ft_strdup.c ft_memchr.c ft_strnstr.c ft_substr.c \
	   ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putendl_fd.c \
	   ft_putstr_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_strmapi.c \
	   ft_striteri.c get_next_line.c get_next_line_utils.c \
	   ft_formating.c ft_puthex_opt.c ft_putstr_opt.c ft_putuns_opt.c \
	   ft_putptr_opt.c ft_putchar_opt.c ft_putnbr_opt.c ft_justify.c \
	   ft_printf.c 

SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			 ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			 ft_lstmap_bonus.c exit_error.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all : ${NAME}
	
${NAME} : ${OBJS_BONUS} ${OBJS}
	ar rc ${NAME} ${OBJS} ${OBJS_BONUS}

clean :
	rm -f ${OBJS} ${OBJS_BONUS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re



