/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:27:19 by mohifdi           #+#    #+#             */
/*   Updated: 2025/12/11 15:27:44 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_shell *shell)
{
	int	i;
	t_shell tmp;

	tmp = *shell;
	if (!tmp.env)
	{
		ft_putstr_fd("minishell: env: environment not found\n", 2);
		return ;
	}
	i = 0;
	while (tmp.env[i])
	{
		if (ft_strchr(tmp.env[i], '=') != NULL)
		{
			write(1, tmp.env[i], ft_strlen(tmp.env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}