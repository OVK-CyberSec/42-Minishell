 #include "../includes/minishell.h"


int	check_files(int ac, char **av)
{
	int	fd;

	
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		perror("pipex: infile");
	close(fd);
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("pipex: outfile");
		return (0);
	}
	close(fd);
	return (1);
}

static int	check_local_command(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	ft_putstr_fd("minishell: no such file or permission denied: ", 2);
	ft_putendl_fd(cmd, 2);
	return (0);
}

static int	check_path_command(char *cmd, char **env)
{
	char	*path;

	path = get_path(cmd, env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		return (0);
	}
	free(path);
	return (1);
}

static int	check_single_command(char *cmd, char **env)
{
	char	**cmd_parts;
	int		result;

	cmd_parts = ft_split(cmd, ' ');
	if (!cmd_parts)
	{
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
		return (0);
	}
	if (ft_strchr(cmd_parts[0], '/'))
		result = check_local_command(cmd_parts[0]);
	else
		result = check_path_command(cmd, env);
	ft_free_tab(cmd_parts);
	return (result);
}

int	check_commands(char **av, char **env)
{
	if (!check_single_command(av[2], env))
		return (0);
	if (!check_single_command(av[3], env))
		return (0);
	return (1);
}
