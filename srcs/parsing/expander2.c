/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:35:05 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:35:06 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unq(char **res, char *str, int *i)
{
	char	*part;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '$'
		&& str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	part = ft_substr(str, start, *i - start);
	*res = str_append(*res, part);
	free(part);
}

static int	is_pure_expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (0);
		else if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				i++;
			else
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
			}
		}
		else
			return (0);
	}
	return (1);
}

static t_token	*remove_token(t_token *tok, t_token *prev,
								t_token **head)
{
	t_token	*next;

	next = tok->next;
	if (prev)
		prev->next = next;
	else
		*head = next;
	free(tok->value);
	free(tok);
	return (next);
}

static int	process_word_token(t_token **tok_ptr, t_token *prev,
								t_token **head, t_data *data)
{
	char	*expanded;
	int		pure;
	t_token	*tok;

	tok = *tok_ptr;
	pure = is_pure_expansion(tok->value);
	expanded = expand_token(tok->value, data);
	free(tok->value);
	tok->value = expanded;
	if (pure && tok->value && !tok->value[0])
	{
		*tok_ptr = remove_token(tok, prev, head);
		return (1);
	}
	return (0);
}

void	expand_variables(t_token **tokens_ptr, t_data *data)
{
	t_token	*prev;
	t_token	*tmp;

	prev = NULL;
	tmp = *tokens_ptr;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			if (process_word_token(&tmp, prev, tokens_ptr, data))
				continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
