#include "../../includes/minishell.h"

static int	env_key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*get_env_value(char **env, const char *key)
{
	int		i;
	int		klen;
	int		elen;

	if (!env || !key)
		return (NULL);
	klen = strlen(key);
	i = 0;
	while (env[i])
	{
		elen = env_key_len(env[i]);
		if (elen == klen && strncmp(env[i], key, klen) == 0)
			return (env[i] + elen + 1);
		i++;
	}
	return (NULL);
}


static char *make_env_var(const char *key, const char *value)
{
    size_t len = strlen(key) + strlen(value) + 2;
    char *res = malloc(len);
    if (!res)
        return NULL;
    snprintf(res, len, "%s=%s", key, value);
    return res;
}

void update_env_value(t_shell *shell, const char *key, const char *value)
{
    int i;
    int key_len;

    if (!shell || !shell->env || !key || !value)
        return;
    i = 0;
    key_len = strlen(key);
    while (shell->env[i])
    {
        if (strncmp(shell->env[i], key, key_len) == 0 
                && shell->env[i][key_len] == '=')
        {
            free(shell->env[i]);
            shell->env[i] = make_env_var(key, value);
            return;
        }
        i++;
    }
}

// void update_env_value(t_shell *shell, char *val)
// {
//     int len;

//     len = ft_strlen(shell->env);
       
// }

int is_valid_identifier(const char *s)
{
    int i;

    if (!s || !s[0])
        return 0;

    if (!(ft_isalpha(s[0]) || s[0] == '_'))
        return 0;

    i = 1;
    while (s[i])
    {
        if (!(ft_isalnum(s[i]) || s[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}

// void *sort_tab(char **env)
// {
//     int i;
//     int j;
//     char *tmp;

//     i = 0;
//     if (!array)
//         return;

//     while (array[i])
//     {
//         j = i + 1;
//         while (array[j])
//         {
//             if (strcmp(array[i], array[j]) > 0)
//             {
//                 tmp = array[i];
//                 array[i] = array[j];
//                 array[j] = tmp;
//             }
//             j++;
//         }
//         i++;
//     }
// }

void free_tab(char **tab)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int is_key_found(t_shell *shell, char *key)
{
    int i;
    char **tmp;

    if (!(shell || key || shell->env))
        return (0);
    tmp = shell->env;
    i = 0;
    while (tmp[i])
    {
        if (ft_strncmp(key, tmp[i],ft_strlen(key)) == 0
                && ft_strlen(key) + 1 == '=')
            return (1);
        i++;
    }
    return (0);
}

// }

// t_env *copy_env_list(t_env *env)
// {
//     t_env *copy = NULL;
//     t_env *tmp;

//     while (env)
//     {
//         tmp = malloc(sizeof(t_env));
//         if (!tmp)
//             return (NULL);
//         tmp->key = strdup(env->key);
//         tmp->value = strdup(env->value);
//         tmp->next = copy;
//         copy = tmp;
//         env = env->next;
//     }
//     return (copy);
// }

// void free_env_list(t_env *env)
// {
//     t_env *tmp;

//     while (env)
//     {
//         tmp = env;
//         env = env->next;
//         free(tmp->key);
//         free(tmp->value);
//         free(tmp);
//     }
// }