/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:58:00 by iobba             #+#    #+#             */
/*   Updated: 2023/03/10 12:50:06 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_vo_path(t_env **my_env, char *cmd)
{
	t_env	*ptr;

	ptr = *my_env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, "PATH", 4))
			return (ptr->value);
		ptr = ptr->next;
	}
	if (access(cmd, F_OK) == 0)
		return (NULL);
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	exit (127);
}

char	*get_path(t_env **my_env, char *cmd)
{
	char		*value_of_path;
	char		**arr;
	int			j;
	char		*filename;
	char		*with_slash;

	j = 0;
	value_of_path = get_vo_path(my_env, cmd);
	if (!value_of_path)
		return (ft_strdup(cmd));
	arr = ft_split(value_of_path, ':');
	while (arr[j])
	{
		with_slash = ft_strjoin(arr[j++], "/");
		filename = ft_strjoin(with_slash, cmd);
		free(with_slash);
		if (access(filename, F_OK) == 0)
		{
			freeing(arr);
			return (filename);
		}
		free(filename);
	}
	return (freeing(arr), NULL);
}

char	**into_arr(t_cmd *cmd)
{
	char	**arr;
	int		i;

	i = 0;
	while (cmd->args[i])
		i++;
	arr = malloc((i + 2) * sizeof(char *));
	if (!arr)
		error_exit("allocation");
	arr[0] = cmd->cmd;
	i = 0;
	while (cmd->args[i])
	{
		arr[i + 1] = cmd->args[i];
		i++;
	}
	arr[i + 1] = NULL;
	return (arr);
}

void	dup2_and_close(int fd_in, int fd_out, int in_of_next)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in > 0)
		close(fd_in);
	if (fd_out > 1)
		close(fd_out);
	if (in_of_next > 0)
		close (in_of_next);
}

void	ft_execve(t_cmd *cmd, t_env **my_env, int fd_in, int fd_out)
{
	char	**arr;
	char	*filename;
	char	**env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2_and_close(fd_in, fd_out, cmd->in_of_next);
	arr = into_arr(cmd);
	if (ft_strchr(arr[0], '/') && !access(arr[0], F_OK))
		filename = arr[0];
	else if (ft_strchr(arr[0], '/') && access(arr[0], F_OK))
		no_cmd_file(arr, ": No such file or directory");
	else
	{
		filename = get_path(my_env, arr[0]);
		if (!filename)
			no_cmd_file(arr, ": command not found");
	}
	env = env_arr(*my_env);
	if (execve(filename, arr, env) == -1)
		error_execve(cmd->cmd);
}
