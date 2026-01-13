/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:35:47 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:35:48 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *cmd, char *msg)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	exit_error(char *msg, int code)
{
	print_error(NULL, msg);
	exit(code);
}
