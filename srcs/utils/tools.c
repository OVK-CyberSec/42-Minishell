#include "../../includes/minishell.h"


bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (true);
	return (false);
}

int	is_special(char *str)
{
	int len;

	if (!str)
	len = ft_strlen(str);
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(str, ">>", 2))
			return (APPEND);
	}
	if (len >= 1)
	{
		if (str[0] == '<')
			return (INPUT);
		if (str[0] == '>')
			return (TRUNC);
		if (str[0] == '|')
			return (PIPE);
	}
	return (0);
}

int	is_command()