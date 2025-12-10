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

t_cmd	*parse_simple_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg_to_cmd(cmd, tokens->value);
		else if (is_redirection(tokens->type))
			tokens = handle_redirection(cmd, tokens);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = NULL;
	current = parse_simple_cmd(tokens);
	if (current)
		cmds = current;
	return (cmds);
}

