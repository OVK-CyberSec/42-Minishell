/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnakasto <mnakasto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:26:56 by mnakasto          #+#    #+#             */
/*   Updated: 2025/12/10 20:41:02 by mnakasto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_one_cmd(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			add_arg_to_cmd(cmd, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else if (is_redirection((*tokens)->type))
			*tokens = handle_redirection(cmd, *tokens);
		else
			*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	t_cmd	*last;

	cmds = NULL;
	last = NULL;
	while (tokens)
	{
		current = parse_one_cmd(&tokens);
		if (!current)
			break ;
		if (!cmds)
			cmds = current;
		else
			last->next = current;
		last = current;
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}

