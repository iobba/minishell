/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:54:07 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:33:13 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		return (1);
	return (0);
}

int	pick_and_exec(t_cmd *cmd, t_general *all, int fd_out, int i)
{
	t_env	**my_env;

	my_env = &(all->env_list);
	if (!ft_strncmp(cmd->cmd, "cd", 3))
		return (ft_cd(cmd->args, my_env, fd_out));
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		return (ft_echo(cmd->args, fd_out));
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		return (ft_env(*my_env, fd_out));
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		return (ft_export(cmd->args, my_env, fd_out));
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		return (ft_pwd(fd_out));
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		return (ft_unset(my_env, cmd->args));
	return (ft_exit(cmd->args, i));
}

int	should_fork(t_cmd *cmd)
{
	if (cmd->sep == pipe_op)
		return (1);
	if (cmd->prev && cmd->prev->sep == pipe_op)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_general *all, int fd_out, int fd_in)
{
	int	pid;

	if (should_fork(cmd) == 0)
		return (pick_and_exec(cmd, all, fd_out, 1));
	pid = fork();
	if (pid == 0)
	{
		if (fd_in > 0)
			close(fd_in);
		if (cmd->in_of_next > 0)
			close(cmd->in_of_next);
		exit(pick_and_exec(cmd, all, fd_out, 0));
	}
	if (pid > 0)
		return (ft_wait_child(pid, cmd, fd_in, fd_out));
	else
		error_exit("minishell");
	return (EXIT_SUCCESS);
}
