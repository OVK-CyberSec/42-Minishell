/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:33:48 by mohifdi           #+#    #+#             */
/*   Updated: 2026/02/04 10:38:35 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child(t_cmd *cmd, t_data *data, t_pipex *px)
{
	setup_pipes(px);
	if (setup_redirections(cmd->redirs, data) != 0)
		exit(1);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, data));
	exec_binary(cmd, data);
}

static void	init_pipex(t_pipex *px, t_cmd *cmds)
{
	px->n = count_cmds(cmds);
	px->i = 0;
	px->pipes = malloc(sizeof(int *) * (px->n - 1));
	if (!px->pipes && px->n > 1)
		exit_error("malloc failed", 1);
	px->pids = malloc(sizeof(pid_t) * px->n);
	if (!px->pids)
	{
		free(px->pipes);
		exit_error("malloc failed", 1);
	}
}

static void	create_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->n - 1)
	{
		px->pipes[i] = malloc(2 * sizeof(int));
		if (!px->pipes[i])
			exit_error("malloc failed", 1);
		if (pipe(px->pipes[i]) == -1)
			exit_error("pipe failed", 1);
		i++;
	}
}

static void	cleanup_pipex(t_pipex *px)
{
	int	j;

	j = 0;
	while (j < px->n - 1)
	{
		free(px->pipes[j]);
		j++;
	}
	free(px->pipes);
	free(px->pids);
}

void	execute_pipeline(t_cmd *cmds, t_data *data)
{
	t_pipex	px;
	int		status;

	init_pipex(&px, cmds);
	create_pipes(&px);
	while (cmds)
	{
		px.pids[px.i] = fork();
		if (px.pids[px.i] == 0)
			exec_child(cmds, data, &px);
		cmds = cmds->next;
		px.i++;
	}
	close_all_pipes(&px);
	wait_all_pids(&px, &status);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	cleanup_pipex(&px);
}
