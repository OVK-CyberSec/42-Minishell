#include "../../includes/minishell.h"

static t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

static int	get_token_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(str, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(str, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(str, ">>"))
		return (TOKEN_REDIR_APPEND);
	if (!ft_strcmp(str, "<<"))
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
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
	while (input[*i] && !ft_isspace(input[*i]) && 
		input[*i] != '|' && input[*i] != '<' && input[*i] != '>' &&
		input[*i] != '\'' && input[*i] != '"')
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
	{
		(*i)++;
		return (ft_strdup("|"));
	}
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			return (ft_strdup("<<"));
		}
		(*i)++;
		return (ft_strdup("<"));
	}
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*i += 2;
			return (ft_strdup(">>"));
		}
		(*i)++;
		return (ft_strdup(">"));
	}
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