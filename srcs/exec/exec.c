#include "../../includes/minishell.h"

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
	// Si execve échoue, on arrive ici
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

void	execute_single_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	if (!cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
		return ((void)(data->exit_status = execute_builtin(cmd, data)));
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

void	execute_commands(t_cmd *cmds, t_data *data)
{
	if (!cmds)
		return ;
	if (!cmds->next)
		execute_single_cmd(cmds, data);
	else
		execute_pipeline(cmds, data);
}
