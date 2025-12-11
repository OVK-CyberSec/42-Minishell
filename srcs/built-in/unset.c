/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:57:50 by mohifdi           #+#    #+#             */
/*   Updated: 2025/12/11 14:01:59 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishellell.h"

static int	handle_err(int id, t_shell *shell, char *str)
{
	if (id == 0)
		printf("unset: %s: invalid parameter name\n", str);
	else if (id == 1)
		printf("unset: not enough arguments\n");
	shell->last_exit = 1;
	return (1);
}

int	remove_env_node(t_shell *shell, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				shell->env_list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	handle_err(0, shell, key);
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	if (!(argv || argv[1]))
		handle_err(1, shell, argv[1]);
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			remove_env_node(shell, argv[i]);
		else
			handle_err(2, shell, argv[1]);
		i++;
	}
	shell->last_exit = 0;
	return (0);
}
