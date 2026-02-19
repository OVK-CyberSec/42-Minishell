/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:35:59 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:36:01 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_valid_id(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_' || !s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	env_key_exists(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*expand_exit_status(int exit_status)
{
	return (ft_itoa(exit_status));
}
