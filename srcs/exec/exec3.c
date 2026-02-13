/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:34:41 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:34:42 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->n - 1)
	{
		close(px->pipes[i][0]);
		close(px->pipes[i][1]);
		i++;
	}
}

void	wait_all_pids(t_pipex *px, int *status)
{
	px->i = 0;
	while (px->i < px->n)
		waitpid(px->pids[px->i++], status, 0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (builtin_echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (builtin_cd(cmd->args, data));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->args[0], "export"))
		return (builtin_export(cmd->args, data));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (builtin_unset(cmd->args, data));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (builtin_env(data));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (builtin_exit(cmd->args, data));
	return (1);
}

void	execute_commands(t_cmd *cmds, t_data *data)
{
	if (!cmds)
		return ;
	if (!cmds->next)
		execute_single_cmd(cmds, data);
	else
		execute_pipeline(cmds, data);
}
