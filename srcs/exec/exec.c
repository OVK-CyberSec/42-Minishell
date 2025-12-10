 #include "../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") \
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") \
	|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") \
	|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
	{
		ft_putstr_fd("minishell: invalid command\n", 2);
		exit(1);
	}
	if (ft_strchr(s_cmd[0], '/') || is_builtin(cmd))
		exec_absolute(s_cmd, env);
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	execve(path, s_cmd, env);
	perror("minishell");
	ft_free_tab(s_cmd);
	free(path);
	exit(0);
}

int	exec_cmd(t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
	
	else
		exec()
		
}

