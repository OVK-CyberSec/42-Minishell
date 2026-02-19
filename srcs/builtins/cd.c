/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:33:39 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:33:40 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd(t_data *data)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		add_env_var(&data->env, "OLDPWD", get_env_value(data->env, "PWD"));
		add_env_var(&data->env, "PWD", cwd);
	}
}

int	builtin_cd(char **args, t_data *data)
{
	char	*path;

	if (args[1] && args[2])
	{
		print_error("cd", "too many arguments");
		return (1);
	}
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
	update_pwd(data);
	return (0);
}
