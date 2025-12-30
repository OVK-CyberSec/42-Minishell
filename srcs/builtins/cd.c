#include "../../includes/minishell.h"

int	builtin_cd(char **args, t_data *data)
{
	char	*path;
	char	cwd[1024];

	if (!args[1])
		path = get_env_value(data->env, "HOME");
	else
		path = args[1];
	if (!path)
	{
		print_error("cd", "HOME not set");
		return (1);
	}
	if (chdir(path) != 0)
	{
		print_error("cd", strerror(errno));
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		add_env_var(&data->env, "OLDPWD", get_env_value(data->env, "PWD"));
		add_env_var(&data->env, "PWD", cwd);
	}
	return (0);
}
