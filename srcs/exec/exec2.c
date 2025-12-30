#include "../../includes/minishell.h"

static int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static void exec_child(t_cmd *cmd, t_data *data, t_pipex *px)
{
    setup_pipes(px);
    setup_redirections(cmd->redirs, data);
    if (is_builtin(cmd->args[0]))
        exit(execute_builtin(cmd, data));
    exec_binary(cmd, data);
}

static void	init_pipex(t_pipex *px, t_cmd *cmds)
{
	px->n = count_cmds(cmds);
	px->i = 0;
	px->pipes = malloc(sizeof(int *) * (px->n - 1));
	px->pids = malloc(sizeof(pid_t) * px->n);
}

static void	create_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->n - 1)
	{
		px->pipes[i] = malloc(2 * sizeof(int));
		pipe(px->pipes[i++]);
	}
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
	px.i = 0;
	while (px.i < px.n)
		waitpid(px.pids[px.i++], &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
