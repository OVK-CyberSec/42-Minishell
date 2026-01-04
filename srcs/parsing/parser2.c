#include "../../includes/minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_cmd(t_cmd **cmds, t_cmd **current, t_cmd *new)
{
	if (!*cmds)
		*cmds = new;
	else
		(*current)->next = new;
	*current = new;
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	t_cmd	*new;

	cmds = NULL;
	current = NULL;
	while (tokens)
	{
		new = create_cmd();
		if (!new)
			return (free_commands(cmds), NULL);
		fill_cmd_args(new, &tokens);
		add_cmd(&cmds, &current, new);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
