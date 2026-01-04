#include "../../includes/minishell.h"

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

void	fill_cmd_args(t_cmd *cmd, t_token **tokens)
{
	t_token	*tmp;
	int		i;
	int		count;

	count = count_args(*tokens);
	cmd->args = malloc(sizeof(char *) * (count + 1));
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
			add_redir(&cmd->redirs,
				create_redir(tmp->type, tmp->next->value));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	*tokens = tmp;
}
