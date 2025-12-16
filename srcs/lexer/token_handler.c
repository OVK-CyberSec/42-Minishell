#include "../../includes/minishell.h"

int	handle_pipe(char *input, int i, t_token **tokens)
{
	(void)input;
	add_token(tokens, TOKEN_PIPE, "|");
	return (i + 1);
}

int	handle_redir_out(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '>')
	{
		add_token(tokens, REDIR_APPEND, ">>");
		return (i + 2);
	}
	else
	{
		add_token(tokens, REDIR_OUT, ">");
		return (i + 1);
	}
}

int	handle_redir_in(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '<')
	{
		add_token(tokens, REDIR_HEREDOC, "<<");
		return (i + 2);
	}
	else
	{
		add_token(tokens, REDIR_IN, "<");
		return (i + 1);
	}
}

int	handle_quotes(char *input, int i, t_token **tokens)
{
	char	quote;
	int		start;
	char	*content;

	quote = input[i];
	start = i + 1;
	i++;
	while (input[i] != quote)
		i++;
	if (!input[i])
	{
		printf("Eror: unclosed quote\n");
		return (-1);
	}
	content = ft_substr(input, start, i - start);
	add_token(tokens, TOKEN_WORD, content);
	free(content);
	return (i + 1);
}

// debug function

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("Token[%d]: ", i);
		if (tokens->type == TOKEN_WORD)
			printf("WORD");
		else if (tokens->type == TOKEN_PIPE)
			printf("PIPE");
		else if (tokens->type == REDIR_IN)
			printf("REDIR_IN");
		else if (tokens->type == REDIR_OUT)
			printf("REDIR_OUT");
		else if (tokens->type == REDIR_APPEND)
			printf("REDIR_APPEND");
		else if (tokens->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC");
		else if (tokens->type == TOKEN_VAR)
			printf("VAR");
		printf(" -> \"%s\"\n", tokens->value);
		tokens = tokens->next;
		i++;
	}
}