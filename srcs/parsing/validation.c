/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:35:27 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:35:29 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_syntax(t_token *t)
{
	t_token	*last;

	if (!t || t->type == TOKEN_PIPE)
		return (0);
	while (t)
	{
		if ((t->type == TOKEN_PIPE
				&& (!t->next || t->next->type == TOKEN_PIPE))
			|| (t->type >= TOKEN_REDIR_IN && t->type <= TOKEN_HEREDOC
				&& (!t->next || t->next->type != TOKEN_WORD)))
			return (0);
		last = t;
		t = t->next;
	}
	return (last->type != TOKEN_PIPE);
}
