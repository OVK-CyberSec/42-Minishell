/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:33:57 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:33:59 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->key && env->value == NULL)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static char	*get_export_key(char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

static void	add_export_var(char *arg, char *key, t_data *data)
{
	char	*eq;
	char	*val;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		add_env_var(&data->env, key, NULL);
		return ;
	}
	val = ft_strdup(eq + 1);
	add_env_var(&data->env, key, val);
	free(val);
}

static int	export_one_arg(char *arg, t_data *data)
{
	char	*key;

	key = get_export_key(arg);
	if (!is_valid_id(key))
	{
		print_error(arg, ": not a valid identifier");
		free(key);
		return (1);
	}
	add_export_var(arg, key, data);
	free(key);
	return (0);
}

int	builtin_export(char **args, t_data *data)
{
	int	i;
	int	ret;

	if (!args[1])
		return (print_export(data->env), 0);
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (export_one_arg(args[i], data))
			ret = 1;
		i++;
	}
	return (ret);
}
