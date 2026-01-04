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

static char	*extract_quoted_string(char *input, int *i, char quote)
{
	int		start;
	char	*result;

	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	result = ft_substr(input, start, *i - start);
	if (input[*i] == quote)
		(*i)++;
	return (result);
}

static char	*extract_word(char *input, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	result = ft_substr(input, start, *i - start);
	return (result);
}

static char	*get_next_token_value(char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (input[*i] == '\'' || input[*i] == '"')
		return (extract_quoted_string(input, i, input[*i]));
	if (input[*i] == '|')
		return ((*i)++, ft_strdup("|"));
	if (input[*i] == '<' || input[*i] == '>')
		return (handle_redir(input, i, input[*i]));
	return (extract_word(input, i));
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
