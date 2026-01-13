/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:33:52 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:33:53 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_exit(char **args, t_data *data)
{
	int	exit_code;

	printf("exit\n");
	if (args[1])
	{
		exit_code = atoi(args[1]);
		cleanup_data(data);
		exit(exit_code);
	}
	cleanup_data(data);
	exit(data->exit_status);
}
