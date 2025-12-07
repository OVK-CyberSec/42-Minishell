#include "minishell.h"

void exec_cd(t_command *arg, t_exit exit)
{
    if (argc == 0)
        chdir("~");
    else if (valid_commmand())
    {
        chdir(arg->cmd);
        exit.id = 0;
    }
    else if (!(valid_commmand()))
        cd_err_msg(arg, exit);
}


void cd_err_msg(t_command *arg, t_exit exit)
{
    printf("cd: no such file or directory: %s\n", arg);
    exit.id = 1;
    return ;
}