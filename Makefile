SRCS = 	parsing/launch_shell.c  parsing/debugger.c\
		parsing/tokenization.c parsing/tokendup.c \
		parsing/check_syntax.c parsing/check_syntax_utils.c \
		parsing/param_expansion.c  parsing/param_expansion_utils.c\
		parsing/gllobing.c parsing/gllobing_utils.c \
		parsing/quotes_handling.c parsing/parsing_utils1.c \
		parsing/grammar.c parsing/grammar_utils1.c parsing/grammar_utils2.c \
		execution/manage_redirections.c execution/manage_errors.c execution/exec_utils.c execution/clearing.c \
		execution/exec_all_cmds.c execution/fill_here_doc.c execution/exec_builtin.c execution/ft_execve.c execution/here_doc_expansion.c \
		builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_export.c \
		builtin/ft_pwd.c builtin/ft_unset.c builtin/ft_exit.c builtin/builtin_utils.c \
		

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

all : ${NAME}

%.o: %.c
	cc -g  -I/goinfre/isalhi/homebrew/opt/readline/include -c $< -o $@

${NAME} : ${OBJS}
	make -C libft/
	cc ${OBJS} ${CFLAGS} libft/libft.a  -L/goinfre/isalhi/homebrew/opt/readline/lib -lreadline -o ${NAME} 


clean :
	make clean -C libft
	rm -f ${OBJS}

fclean : clean
	make clean -C libft
	rm -f ${NAME}

re : fclean all
