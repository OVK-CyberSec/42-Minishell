
#include "../../includes/minishell.h"

void exec_echo(t_command *cmd, t_exit exit)
{
    int i;

    if (valid_commmand() && cmd->arg[1])
    {
        printf("%s",cmd->arg[1]);
        exit.id = 0;
    }
    else if (valid_commmand())
        
        return 0
}



static int valid_commmand()