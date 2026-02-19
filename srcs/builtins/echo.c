/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:33:43 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:33:45 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	newline = 1;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][j] && args[i][++j] == 'n')
			newline = 0;
		if (args[i][j])
			break ;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
