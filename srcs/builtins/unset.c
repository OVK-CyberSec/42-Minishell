/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:34:08 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:34:10 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
