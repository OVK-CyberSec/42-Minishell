/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:34:04 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:34:05 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_data *data)
{
	char	*pwd;
	char	cwd[1024];

	pwd = get_env_value(data->env, "PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	print_error("pwd", strerror(errno));
	return (1);
}
