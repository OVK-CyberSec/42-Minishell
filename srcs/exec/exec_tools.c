#include "../../includes/minishell.h"

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	i = -1;
	while (allpath && allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(s_cmd);
	ft_free_tab(allpath);
	return (NULL);
}

// void	exec_absolute(t_cmd *cmd, char **env, t_shell *shell)
// {
// 	if (access(cmd->args[0], F_OK | X_OK) == 0)
// 	{
// 		execve(cmd->args[0], cmd->args, env);
// 		perror("minishell");
// 		shell->last_exit = 0;
// 	}
// 	else
// 	{
// 		printf("minishell: no such file or directory: %s", cmd->args[0]);
// 		shell->last_exit = 127;
// 	}
// 	//ft_free_tab(cmd->args[0]);
// }

void	exec_absolute(char **cmd, char **env, t_shell *shell)
{
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		execve(cmd[0], cmd, env);
		perror("minishell");
		shell->last_exit = 0;
	}
	else
	{
		printf("minishell: no such file or directory: %s", cmd[0]);
		shell->last_exit = 127;
	}
	//ft_free_tab(cmd->args[0]);
}