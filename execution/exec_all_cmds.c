/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:31:53 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:33:48 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_wait_child(pid_t pid, t_cmd *cmd, int fd_in, int fd_out)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (fd_in > 0)
		close(fd_in);
	if (fd_out > 1)
		close(fd_out);
	if (cmd->sep != pipe_op)
	{
		if (waitpid(pid, &status, 0) == -1)
			error_exit("waitpid failed");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write (2, "^\\Quit: 3\n", 10);
			return (WTERMSIG(status) + 128);
		}
	}
	return (status);
}

int	is_empty(char *cmd, int fd_in, int fd_out)
{
	if (fd_in > 0)
		close(fd_in);
	if (fd_out > 1)
		close(fd_out);
	if (cmd == NULL)
		return (EXIT_SUCCESS);
	if (cmd[0] == '\0')
	{
		print_error("minishell: ", "", ": command not found");
		return (127);
	}
	return (EXIT_SUCCESS);
}

int	exec_command(t_cmd *cmd, t_env **my_env, t_general *all)
{
	pid_t	pid;
	int		fd_out;
	int		fd_in;

	if (set_in_out_fds(cmd, &fd_in, &fd_out))
		return (EXIT_FAILURE);
	if (cmd->cmd == NULL || cmd->cmd[0] == '\0')
		return (is_empty(cmd->cmd, fd_in, fd_out));
	if (is_dots(cmd->cmd, 0))
		return (is_dots(cmd->cmd, 1));
	if (is_dir(cmd->cmd))
		return (126);
	if (is_builtin(cmd))
		return (exec_builtin(cmd, all, fd_out, fd_in));
	pid = fork();
	if (pid == 0)
		ft_execve(cmd, my_env, fd_in, fd_out);
	if (pid > 0)
		return (ft_wait_child(pid, cmd, fd_in, fd_out));
	else
		error_exit("minishell");
	return (EXIT_SUCCESS);
}

int	ignore_cmds(t_cmd *cmd, int lvl)
{
	if (lvl == -1)
	{
		if (cmd && (cmd->sep == or_op || cmd->sep == pipe_op))
			return (1);
		if (cmd && cmd->sep == and_op && cmd->level > cmd->prev->level)
			return (1);
	}
	else
	{
		if (cmd && (cmd->sep == and_op || cmd->sep == pipe_op))
			return (1);
		if (cmd && cmd->sep == or_op && cmd->level > lvl)
			return (1);
	}
	return (0);
}

void	exec_all_cmds(t_cmd **all_cmds, t_general *all)
{
	t_cmd		*cmd;
	int			lvl;

	cmd = *all_cmds;
	while (cmd)
	{
		g_last_exit = exec_command(cmd, &(all->env_list), all);
		if (g_last_exit == 0 && cmd->sep == or_op)
		{
			cmd = cmd->next;
			while (ignore_cmds(cmd, -1))
				cmd = cmd->next;
		}
		else if (g_last_exit && cmd->sep == and_op)
		{
			lvl = cmd->level;
			cmd = cmd->next;
			while (ignore_cmds(cmd, lvl))
				cmd = cmd->next;
		}
		if (cmd)
			cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
}
