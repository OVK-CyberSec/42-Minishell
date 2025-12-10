#include "minishell.h"

int builtin_cd(char **args, t_shell *shell)
{
    char *path;
    char *old_pwd;
    char cwd[PATH_MAX];

    path = args[1];
    if (!path)
    {
        path = get_env_value(shell->env, "HOME");
        if (!path)
            handle_err_cd(0, path, shell);
    }
    old_pwd = ft_strdup(get_env_value(shell->env, "PWD"));
    if (chdir(path) == -1)
    {
        handle_err_cd(1, path, shell);
        free(old_pwd);
        return 1;
    }
    update_env_value(shell, "OLDPWD", old_pwd);
    free(old_pwd);
    if (getcwd(cwd, sizeof(cwd)))
        update_env_value(shell, "PWD", cwd);
    shell->last_exit = 0;
    return 0;
}


int handle_err_cd(int id, char *str, t_shell shell)
{
    if (id == 0)
    {
        printf("cd: HOME not set\n");
        return 1;
    }
    else if (id == 1)
    {
        printf("cd: no such file or directory: %s", str);
    }
    shell->last_exit = 1;
}