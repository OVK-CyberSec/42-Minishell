/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:23:13 by mohifdi           #+#    #+#             */
/*   Updated: 2025/12/11 15:27:08 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_id(char *arg, char *equal)
{
	int		i;
	int		len;

	if (!arg || !arg[0])
		return (0);
	if (equal)
		len = equal - arg;
	else
		len = ft_strlen(arg);
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_env_sorted(t_shell *shell)
{
	char	**sorted;
	int i;

	if (!(shell->env))
		return ;
	sorted = shell->env;
	if (!(sorted))
		return ;
	sort_tab(sorted);
	i = 0;
	while (sorted[i])
	{
		printf("%s\n", sorted[i]);
		i++;
	}
	free_tab(sorted);
}

void	mark_as_exported(t_shell *shell, char *key)
{
	t_env	*var;

	if (is_key_found(shell->env, key))
		return ;
	var = find_env(shell->env, key); // last 
	if (var)
		var->exported = 1;
	add_env(&shell->env, key, "");
}	

static void	process_export_arg(char *arg, t_shell *shell)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!is_valid_id(arg, equal))
	{
		printf("export: not an identifier: %s\n", arg);
		shell->exit_status = 1;
		return ;
	}
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
		update_env(&shell->env, key, value);
		free(key);
		free(value);
	}
	else
		mark_as_exported(shell, arg);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		print_env_sorted(shell->env);
		return (0);
	}
	while (args[i])
	{
		process_export_arg(args[i], shell);
		i++;
	}
	return (0);
}
