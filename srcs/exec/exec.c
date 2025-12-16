 #include "../../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") \
	|| !strcmp(cmd, "pwd") || !strcmp(cmd, "export") \
	|| !strcmp(cmd, "unset") || !strcmp(cmd, "env") \
	|| !strcmp(cmd, "exit"))
		return (true);
	return (false);
}

void	exec_builtin(char **cmd, t_shell *shell)
{
	if (strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
	else if (strcmp(cmd[0], "cd") == 0)
		builtin_cd(cmd, shell);
	else if (strcmp(cmd[0], "env") == 0)
	 	builtin_env(shell);
	else if (strcmp(cmd[0], "pwd") == 0)
	 	builtin_pwd(shell);
	//  else if (strcmp(cmd[0], "export") == 0)
	//   	builtin_export(cmd, shell);
	else if (strcmp(cmd[0], "unset") == 0)
	 	builtin_unset(cmd, shell);
	// else if (strcmp(*cmd, "exit"))
	// 	builtin_exit(env, shell);
}

// int	exec_native(t_cmd *cmd, t_shell *shell, char **env)
// {
// 	char	*path;

// 	// s_cmd = ft_split(cmd->&args, ' ');
// 	// if (!s_cmd || !s_cmd[0])
// 	// 	return (0);
// 	if (ft_strchr(cmd->args[0], '/'))
// 		exec_absolute(cmd, env, shell);
// 	path = get_path(cmd->args[0], env);
// 	if (!path)
// 	{
// 		printf("minishell: command not found: %s", cmd->args[0]);
// 		shell->last_exit = 127;
// 		//ft_free_tab(s_cmd);
// 		return (1);
// 	}
// 	execve(path, cmd->args, env);
// 	perror("minishell");
// 	// ft_free_tab(s_cmd);
// 	free(path);
// 	return (0);
// }

int	exec_native(char **cmd, t_shell *shell, char **env)
{
	char	*path;

	// s_cmd = ft_split(cmd->&args, ' ');
	// if (!s_cmd || !s_cmd[0])
	// 	return (0);
	if (ft_strchr(cmd[0], '/'))
		exec_absolute(cmd, env, shell);
	path = get_path(cmd[0], env);
	if (!path)
	{
		printf("minishell: command not found: %s\n", cmd[0]);
		shell->last_exit = 127;
		//ft_free_tab(s_cmd);
		return (1);
	}
	if (execve(path, cmd, env) == -1)
		exit(EXIT_FAILURE);
	perror("minishell");
	// ft_free_tab(s_cmd);
	free(path);
	return (0);
}

int	exec_cmd(char **cmd, t_shell *shell)
{
	if (is_builtin(cmd[0]))
		exec_builtin(cmd, shell);
	else
		exec_native(cmd, shell, shell->env);
	return (0);
}

// int	exec_cmd(t_cmd *cmd, t_shell *shell)
// {
// 	if (is_builtin(cmd->args[0]))
// 		exec_builtin(cmd->args, shell);
// 	else
// 		exec_native(cmd, shell, shell->env);
// 	return 0;		
// }

// int	handle_error(int id, char *str, t_shell *shell)
// {
// 	if (id == 0)
// 	{
// 		printf("");
// 		shell->last_exit = 127;
// 	}
// 	else if (id == 1)
// 	{
// 		printf("");
// 		shell->last_exit = ;
// 	}
// }