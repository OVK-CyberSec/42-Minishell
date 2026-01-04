#include "../../includes/minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
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

static char	*handle_var(char *res, char *str, int *i, t_data *data)
{
	char	*name;
	char	*value;

	name = get_var_name(str, i);
	if (!ft_strcmp(name, "?"))
		value = expand_exit_status(data->exit_status);
	else
		value = get_env_value(data->env, name);
	if (value)
	{
		res = join_and_free(res, value);
		if (!ft_strcmp(name, "?"))
			free(value);
	}
	free(name);
	return (res);
}

static char	*expand_variable(char *str, t_data *data)
{
	char	*res;
	int		i;
	int		start;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		if (i > start)
			res = join_and_free(res, ft_substr(str, start, i - start));
		if (str[i] == '$')
			res = handle_var(res, str, &i, data);
	}
	return (res);
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
