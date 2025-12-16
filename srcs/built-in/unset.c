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

#include "../../includes/minishell.h"

static int	handle_err(int id, t_shell *shell, char *str)
{
	if (id == 0)
		printf("unset: %s: invalid parameter name\n", str);
	else if (id == 1)
		printf("unset: not enough arguments\n");
	shell->last_exit = 1;
	return (1);
}

static void remove_env_entry(t_shell *shell, int index)
{
    int i;
	int size;

	i = 0;
    while (shell->env[i])
        i++;
    size = i;
    free(shell->env[index]);
	i = index;
    while (i < size - 1)
	{
        shell->env[i] = shell->env[i + 1];
		i++;
	}
    shell->env[size - 1] = NULL;
}

static void remove_by_key(t_shell *shell, const char *key)
{
	char *sep;
	int len;
    int key_len;
	int i;

	key_len = ft_strlen(key);
	i = 0;
    while (shell->env[i] != NULL)
    {
        sep = ft_strchr(shell->env[i], '=');
        if (!sep)
            continue;
        len = sep - shell->env[i];
        if (len == key_len && strncmp(shell->env[i], key, key_len) == 0)
        {
            remove_env_entry(shell, i);
            return;
        }
		i++;
    }
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
			remove_by_key(shell, argv[i]);
		else
			handle_err(0, shell, argv[1]);
		i++;
	}
	shell->last_exit = 0;
	return (0);
}
