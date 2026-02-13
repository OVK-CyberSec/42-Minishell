/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:33:36 by mohifdi           #+#    #+#             */
/*   Updated: 2026/02/04 10:33:38 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*create_env_var(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (!(env->key))
		return (NULL);
	env->value = ft_strdup(value);
	if (!(env->value))
		return (NULL);
	env->next = NULL;
	return (env);
}

static t_env	*ft_env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_var;
	char	*eq;
	char	*key_tmp;
	int		i;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			key_tmp = ft_substr(envp[i], 0, eq - envp[i]);
			new_var = create_env_var(key_tmp, eq + 1);
			if (!new_var)
				return (NULL);
			free(key_tmp);
			if (!env)
				env = new_var;
			else
				ft_env_last(env)->next = new_var;
		}
	}
	return (env);
}

void	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	if (!key)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		*env = create_env_var(key, value);
	else
		tmp->next = create_env_var(key, value);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	char	*line;
	int		i;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		line = ft_strjoin(tmp->key, "=");
		envp[i++] = ft_strjoin(line, tmp->value);
		free(line);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
