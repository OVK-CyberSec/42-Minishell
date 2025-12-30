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

static t_redir	*create_redir(int type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

static void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

static int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		else if (tmp->type >= TOKEN_REDIR_IN && tmp->type <= TOKEN_HEREDOC)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (count);
}

static void	fill_cmd_args(t_cmd *cmd, t_token **tokens)
{
	int		i;
	int		arg_count;
	t_token	*tmp;

	arg_count = count_args(*tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return ;
	i = 0;
	tmp = *tokens;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			cmd->args[i++] = ft_strdup(tmp->value);
		else if (tmp->type >= TOKEN_REDIR_IN && tmp->type <= TOKEN_HEREDOC)
		{
			add_redir(&cmd->redirs, create_redir(tmp->type, tmp->next->value));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	*tokens = tmp;
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	t_cmd	*new_cmd;

	if (!tokens)
		return (NULL);
	cmds = NULL;
	current = NULL;
	while (tokens)
	{
		new_cmd = create_cmd();
		if (!new_cmd)
		{
			free_commands(cmds);
			return (NULL);
		}
		fill_cmd_args(new_cmd, &tokens);
		if (!cmds)
			cmds = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}