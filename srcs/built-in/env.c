

void print_env(t_command *cmd, t_exit exit)
{
    char **env;

    env = environ;
    if (!cmd)
        return ;
    if (valid_commmand())
    {
        printf("%s\n",env);
        exit.id = 0;
    }
    else
    {
        printf("minishell: command not found: %s\n",*cmd);
        exit.id = 1;
    }
}