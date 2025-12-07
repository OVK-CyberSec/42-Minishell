#include "../../includes/minishell.h"

int is_valid_identifier(char *arg, char *equal)
{
    int i;

    i = 0;
    if (!arg || !arg[0])
        return (0);
    if (equal)
        arg[equal - arg] = '\0';
    if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
        return (0);
    i = 1;
    while (arg[i])
    {
        if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

void mark_as_exported(t_shell *shell, char *key)
{
    t_env *var;

    var = find_env(shell->env, key);
    if (var)
        var->exported = 1;
        add_env(&shell->env, key, "");
}

static void process_export_arg(char *arg, t_shell *shell)
{
    char *equal;
    char *key;
    char *value;

    equal = ft_strchr(arg, '=');
    if (!is_valid_identifier(arg, equal))
    {
        ft_putstr_fd("export: `", STDERR);
        ft_putstr_fd(arg, STDERR);
        ft_putstr_fd("': not a valid identifier\n", STDERR);
        shell->exit_status = 1;
        return;
    }
    if (equal)
    {
        key = ft_substr(arg, 0, equal - arg);
        value = ft_strdup(equal + 1);
        update_env(&shell->env, key, value);
        free(key);
        free(value);
    }
    else
        mark_as_exported(shell, arg);
}

int builtin_export(char **args, t_shell *shell)
{
    int i;

    i = 1;
    if (!args[1])
    {
        print_env_sorted(shell->env);
        return 0;
    }
    while (args[i])
    {
        process_export_arg(args[i], shell);
        i++;
    }
    return shell->exit_status;
}
