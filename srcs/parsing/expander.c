#include "../../includes/minishell.h"

static char	*expand_exit_status(int exit_status)
{
	return (ft_itoa(exit_status));
}

static char	*get_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static char	*expand_variable(char *str, t_data *data)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		if (i > start)
		{
			tmp = ft_substr(str, start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
		}
		if (str[i] == '$')
		{
			var_name = get_var_name(str, &i);
			if (!ft_strcmp(var_name, "?"))
				var_value = expand_exit_status(data->exit_status);
			else
				var_value = get_env_value(data->env, var_name);
			if (var_value)
			{
				tmp = result;
				result = ft_strjoin(result, var_value);
				free(tmp);
				if (!ft_strcmp(var_name, "?"))
					free(var_value);
			}
			free(var_name);
		}
	}
	return (result);
}

void	expand_variables(t_token *tokens, t_data *data)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD && ft_strchr(tmp->value, '$'))
		{
			expanded = expand_variable(tmp->value, data);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}