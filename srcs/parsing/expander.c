/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:35:05 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:35:06 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unq(char **res, char *str, int *i);

char	*str_append(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*get_var_name(char *str, int *i)
{
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	return (ft_substr(str, start, *i - start));
}

static char	*handle_var(char *res, char *str, int *i, t_data *data)
{
	char	*name;
	char	*value;

	name = get_var_name(str, i);
	if (!name)
		return (str_append(res, "$"));
	if (!ft_strcmp(name, "?"))
	{
		value = expand_exit_status(data->exit_status);
		res = str_append(res, value);
		free(value);
	}
	else
	{
		value = get_env_value(data->env, name);
		if (value)
			res = str_append(res, value);
	}
	free(name);
	return (res);
}

static void	handle_quote(char **res, char *str, int *i, t_data *data)
{
	char	tmp[2];
	int		q;

	q = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != (char)q)
	{
		if (q == '"' && str[*i] == '$')
			*res = handle_var(*res, str, i, data);
		else
		{
			tmp[0] = str[(*i)++];
			tmp[1] = '\0';
			*res = str_append(*res, tmp);
		}
	}
	if (str[*i] == (char)q)
		(*i)++;
}

char	*expand_token(char *str, t_data *data)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quote(&res, str, &i, data);
		else if (str[i] == '$')
			res = handle_var(res, str, &i, data);
		else
			handle_unq(&res, str, &i);
	}
	return (res);
}
