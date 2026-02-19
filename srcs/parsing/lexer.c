/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:35:08 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:35:09 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_redir(char *input, int *i, char c)
{
	if (input[*i + 1] == c)
	{
		*i += 2;
		if (c == '<')
			return (ft_strdup("<<"));
		return (ft_strdup(">>"));
	}
	(*i)++;
	if (c == '<')
		return (ft_strdup("<"));
	return (ft_strdup(">"));
}

static void	skip_quote(char *input, int *i, char q)
{
	(*i)++;
	while (input[*i] && input[*i] != q)
		(*i)++;
	if (input[*i] == q)
		(*i)++;
}

static char	*build_word(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'')
			skip_quote(input, i, '\'');
		else if (input[*i] == '"')
			skip_quote(input, i, '"');
		else
			(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

static char	*get_next_token_value(char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (input[*i] == '|')
		return ((*i)++, ft_strdup("|"));
	if (input[*i] == '<' || input[*i] == '>')
		return (handle_redir(input, i, input[*i]));
	return (build_word(input, i));
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	char	*value;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		value = get_next_token_value(input, &i);
		if (!value)
			break ;
		new_token = create_token(value, get_token_type(value));
		free(value);
		if (!new_token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, new_token);
	}
	return (tokens);
}
