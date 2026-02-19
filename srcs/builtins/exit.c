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

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_data *data)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		exit_code = data->exit_status;
		cleanup_data(data);
		exit(exit_code);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		cleanup_data(data);
		exit(2);
	}
	if (args[2])
	{
		print_error("exit", "too many arguments");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	cleanup_data(data);
	exit(exit_code);
}
