/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:34:12 by mohifdi           #+#    #+#             */
/*   Updated: 2026/02/04 10:34:13 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	exec_binary(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	**envp;

	path = find_command_path(cmd->args[0], data->env);
	if (!path)
	{
		print_error(cmd->args[0], "command not found");
		exit(CMD_NOT_FOUND);
	}
	envp = env_to_array(data->env);
	if (!envp)
	{
		free(path);
		exit(CMD_NOT_EXECUTABLE);
	}
	execve(path, cmd->args, envp);
	free(path);
	free_split(envp);
	exit(CMD_NOT_EXECUTABLE);
}

void	setup_pipes(t_pipex *px)
{
	int	j;

	if (px->i > 0)
		dup2(px->pipes[px->i - 1][0], STDIN_FILENO);
	if (px->i < px->n - 1)
		dup2(px->pipes[px->i][1], STDOUT_FILENO);
	j = 0;
	while (j < px->n - 1)
	{
		close(px->pipes[j][0]);
		close(px->pipes[j++][1]);
	}
}

static int	exec_builtin_parent(t_cmd *cmd, t_data *data)
{
	int	in;
	int	out;
	int	status;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (setup_redirections(cmd->redirs, data) != 0)
		return (1);
	status = execute_builtin(cmd, data);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	return (status);
}

void	execute_single_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	if (!cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
	{
		data->exit_status = exec_builtin_parent(cmd, data);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		setup_redirections(cmd->redirs, data);
		exec_binary(cmd, data);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
