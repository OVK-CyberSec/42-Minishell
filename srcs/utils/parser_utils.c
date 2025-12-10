/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnakasto <mnakasto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:44:16 by mnakasto          #+#    #+#             */
/*   Updated: 2025/12/10 21:58:59 by mnakasto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;
	int		i;

	i = -1;
	count = 0;
	while (cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * count + 2);
	if (!new_args)
		return ;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

int	is_redirection(t_token_type type)
{
	if (type == REDIR_IN)
		return (1);
	if (type == REDIR_OUT)
		return (1);
	if (type == REDIR_APPEND)
		return (1);
	if (type == REDIR_HEREDOC)
		return (1);
	return (0);
}

void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tmp;
	}

}
t_token	*handle_redirection(t_cmd *cmd, t_token *token)
{
	t_token_type	type;

	type = token->type;
	token = token->next;
	if (!token || token->type == TOKEN_WORD)
		return (NULL);
	add_redir_to_cmd(cmd, type, token->value);
	return (token);
}

void	add_token_to_cmd(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir *new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}



