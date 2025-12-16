
#include "../includes/minishell.h"

char **dup_env(char **envp)
{
    int i;
    char **env;

    i = 0;
    while (envp[i])
        i++;

    env = malloc(sizeof(char *) * (i + 1));
    if (!env)
        return NULL;

    i = 0;
    while (envp[i])
    {
        env[i] = ft_strdup(envp[i]);
        i++;
    }
    env[i] = NULL;
    return env;
}

int main(int ac, char **av, char **env)
{
    char *input;
    char    **cmd;
    t_shell shell;
    t_token token;

    (void)ac;
    (void)av;
    //init_shell(shell, env);
    shell.env = dup_env(env);
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        input = lexer(input);
        if (*input)
            add_history(input);
        cmd = ft_split(input, ' ');
        if (!cmd || !cmd[0])
        {
            free(input);
            free_tab(cmd);
            continue;
        }
        //builtin_cd(cmd, &shell);
        //exec_builtin(cmd, &shell);
        if (exec_pipeline(&cmd, ac, &shell) == 0)
            continue;
        //exec_cmd(input->args, &shell);
       // tokens = lexer(line);
        free(input);
    }
    return (0);
}