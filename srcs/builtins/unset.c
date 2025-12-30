#include "../../includes/minishell.h"

int	builtin_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&data->env, args[i]);
		i++;
	}
	return (0);
}
