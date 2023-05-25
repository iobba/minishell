/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:33:12 by isalhi            #+#    #+#             */
/*   Updated: 2023/03/10 13:33:14 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <limits.h>

int	g_last_exit;

enum e_seps{
	end=1,
	pipe_op=2,
	or_op=3,
	and_op=4,
	o_curly=5,
	c_curly=6,
};

enum e_redirect{
	dless=7,
	less=8,
	great=9,
	dgreat=10
};

typedef struct s_io_redirect
{
	int						io_redirect;
	char					*here_end;
	int						here_doc_expand;
	char					*filename;
	struct s_io_redirect	*next;
}				t_io_redirect;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*here_doc;
	t_io_redirect	*redi_list;
	int				sep;
	int				level;
	int				in_of_next;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env{
	char			*key;
	char			*value;
	int				is_printed;
	struct s_env	*next;
}				t_env;

typedef struct s_general
{
	t_cmd	*all_cmds;
	t_env	*env_list;
	t_list	*tokens;
	int		first_cmd;
}				t_general;

typedef struct s_expand_data
{
	t_list		**tokens;
	t_general	*all;
	int			*ind;
	int			to_split;
	int			*nbr_split;
	char		**arr_words;
	char		*arr;
	char		*arr_next;
}				t_expand_data;
/*///////////  execution  //////////*/

/* main */
void	sig_nal(int sig);

/* builtin */
int		ft_exit(char **arg, int is_print);
int		ft_cd(char **args, t_env **my_env, int fd_out);
int		ft_echo(char **args, int fd_out);
int		ft_export(char **args, t_env **my_env, int fd_out);
int		ft_pwd(int fd_out);
int		ft_unset(t_env **my_env, char **args);
int		ft_env(t_env *env, int fd_out);

/* utils of builtin */
void	ft_setenv(t_env **my_env, char **env);
char	*get_key(char *env_line);
char	*get_var_value(char *env_line);
void	sort_and_show_vars(t_env *my_env, int fd_out);
char	*ft_strjoin_free(char *s1, char *s2);

/* exec_all_cmds */
void	exec_all_cmds(t_cmd **all_cmds, t_general *all);
int		ignore_cmds(t_cmd *cmd, int lvl);
int		exec_command(t_cmd *cmd, t_env **my_env, t_general *all);
int		ft_wait_child(pid_t pid, t_cmd *cmd, int fd_in, int fd_out);

/* exec_builtin */
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_general *all, int fd_out, int fd_in);
int		should_fork(t_cmd *cmd);
int		pick_and_exec(t_cmd *cmd, t_general *all, int fd_out, int i);

/* ft_execve */
void	ft_execve(t_cmd *cmd, t_env **my_env, int fd_in, int fd_out);
void	dup2_and_close(int fd_in, int fd_out, int in_of_next);
char	**into_arr(t_cmd *cmd);
char	*get_path(t_env **my_env, char *cmd);
char	*get_vo_path(t_env **my_env, char *cmd);

/* exec_utils */
int		size_of_env(t_env *my_env);
char	**env_arr(t_env *my_env);
void	freeing(char **str);
int		is_dir(const char *path);
int		is_dots(char *cmd, int print_msg);

/* fill_here_doc */
int		fill_here_doc(t_general *all);
char	*get_name_here_doc(int i);
int		set_here_doc(t_io_redirect *redi, char *name, t_general *all);
int		here_doc_child(t_io_redirect *redi, char *name, t_general *all);
void	here_doc_expansion(char **line, t_general *all);

/* redirections */
int		set_in_out_fds(t_cmd *cmd, int *fd_in, int *fd_out);
int		manage_redirections(t_cmd *cmd, int *fd_in, int *fd_out);
int		close_and_open(int *fd, char *filename, int type);

/* errors */
void	error_exit(char *str);
int		print_error(char *str1, char *str2, char *str3);
int		error_errno(char *str);
void	no_cmd_file(char **arg, char *str);
void	error_execve(char *cmd);

/* clearing and cleaning*/
int		clear_all(t_general *all);

/* parsing */

/* tokenization */

int		is_delimiter(char *s, int index);
int		line_tokenization(char *line, t_general *all);
char	*tokendup(char **line);
char	*tokendup_simple(char **line);
char	*tokendup_dquote(char **line, char c);
char	*ft_strjoin_free(char *s1, char *s2);

/* grammar */
void	parse_tokens(t_general *all, t_list *tokens);
void	ft_cmds_add_back(t_cmd **lst, t_cmd *new);
void	ft_redi_add_back(t_io_redirect **lst, t_io_redirect *new);
void	ft_env_add_back(t_env **lst, t_env *new);
void	init_cmd_elem(t_cmd **cmd_elem, int sep);
void	set_level(int o_parenth, int c_parenth, int *lvl, int *cmd_lvl);
void	expand_tokens(t_general *all, t_list *tokens);
void	skip_parenth(t_list **tokens, int *o_parenth, int *c_parenth);
void	fill_redir(t_general *all, t_list **tokens, t_io_redirect **redir_list);
void	fill_args(t_list **tokens, t_cmd **cmd_elem);

/* debugging */
void	show_tokens(t_list *tokens);
void	show_cmds(t_cmd *cmds);
void	show_redis(t_io_redirect *list);

/* filename expansion */
int		gllobing(t_list *tokens, int *nbr_matchs);
int		get_index(char *token);
void	get_last_index(char *token, int *ind);
int		begin_match(char **haystack, char *needle, int ind);
int		tail_match(char *haystack, char *needle, int ind);
char	*sub_match(char **haystack, char *needle, int ref, int len);
char	*remove_quotes(char *token, int quotes_nbr);
int		count_quotes(char *s);

/* param expansion */
void	param_expansion(t_list *tokens, t_general *all, int *nbr_split);
char	*search_value(char *token, t_expand_data *data, int i);
int		handle_split(char *sub, char *value, int i, t_expand_data *data);
int		handle_variable(char **token, char *sub, char *value, int i);

/* check_syntax */
int		is_sep(char *s);
int		is_redir(char *s);
int		is_curly(char *s);
int		check_syntax(t_list *tokens);
int		check_extra_parenth(t_list *tokens);
#endif
