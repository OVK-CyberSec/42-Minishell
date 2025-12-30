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

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (0);
	tmp = tokens;
	if (tmp->type == TOKEN_PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next || tmp->next->type == TOKEN_PIPE)
				return (0);
		}
		if (tmp->type >= TOKEN_REDIR_IN && tmp->type <= TOKEN_HEREDOC)
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
				return (0);
		}
		tmp = tmp->next;
	}
	if (tokens->type == TOKEN_PIPE)
		return (0);
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == TOKEN_PIPE)
		return (0);
	return (1);
}