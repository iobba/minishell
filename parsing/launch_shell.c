/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:34:57 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:39:19 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	sig_nal(int sig)
{
	struct termios	attr;

	if (sig == -1)
	{
		tcgetattr(STDIN_FILENO, &attr);
		attr.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
	}
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_last_exit = EXIT_FAILURE;
	}
	else if (!sig)
	{
		printf("exit\n");
		exit (0);
	}
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			add_history(line);
			return (0);
		}
		i++;
	}
	if (line[0])
		add_history(line);
	return (1);
}

char	*get_started(t_general *all)
{
	char	*line;

	all->all_cmds = NULL;
	sig_nal(-1);
	signal(SIGINT, &sig_nal);
	signal(SIGQUIT, SIG_IGN);
	line = readline("\033[32mminishell$> \033[0m");
	if (!line)
		sig_nal(0);
	if (check_empty_line(line))
		return (free(line), get_started(all));
	return (line);
}

int	main(int ac, char **av, char **env)
{
	t_general	all;
	char		*line;

	(void) ac;
	(void) av;
	g_last_exit = EXIT_SUCCESS;
	ft_setenv(&(all.env_list), env);
	while (1)
	{
		line = get_started(&all);
		if (line_tokenization(line, &all))
		{
			ft_putendl_fd("minishell: syntax error", 2);
			g_last_exit = 258;
			free(line);
			continue ;
		}
		if (fill_here_doc(&all))
			g_last_exit = EXIT_FAILURE;
		else
			exec_all_cmds(&(all.all_cmds), &all);
		clear_all(&all);
		free(line);
	}
}
