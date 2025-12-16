#include "../../includes/minishell.h"

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|'
			|| c == '>' || c == '<'
			|| c == '\'' || c == '"' || c == '$');
}

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*tokens)
	{
		*tokens = new;
	}
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	handle_dollar(char *input, int i, t_token **tokens)
{
	int		start;
	char	*var;
	
	start = i;
	if (input[i + 1] == '?')
	{
		add_token(tokens, TOKEN_VAR, "$?");
		return (i + 2);
	}
	if (!input[i + 1] || (!ft_isalnum(input[i + 1]) && input[i + 1] != '_'))
	{
		add_token(tokens, TOKEN_WORD, "$");
		return (i + 1);
	}
	i++;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	var = ft_substr(input, start, i - start);
	add_token(tokens, TOKEN_VAR, var);
	free(var);
	return (i);
}

int	handle_word(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;

	start = i;
	while (input[i] && !is_separator(input[i]))
	{
		if (input[i] == '$')
			break;
		i++;
	}
	if (i > start)
	{
		word = ft_substr(input, start, i - start);
		add_token(tokens, TOKEN_WORD, word);
		free(word);
	}
	return (i);
}

t_token *lexer(char *input)
{
	t_token *tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break;
		else if (input[i] == '|')
			i = handle_pipe(input, i, &tokens);
		else if (input[i] == '>')
			i = handle_redir_out(input, i, &tokens);
		else if (input[i] == '<')
			i = handle_redir_in(input, i, &tokens);
		else if (input[i] == '\'' || input[i] == '"')
			i = handle_quotes(input, i, &tokens);
		else if (input[i] == '$')
			i = handle_dollar(input, i, &tokens);
		else 
			i = handle_word(input, i, &tokens);
	}
	return (tokens);
}