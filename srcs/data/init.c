#include "../../includes/minishell.h"

void    init_tokens(t_cmd *cmd, t_token *token)
{
    t_cmd   *tmp;
    int i;

    tmp = cmd;
    if (tmp)
        return ;
    i = 0;
    while(tmp)
    {
        if (is_token(tmp->args[i]))
            token = tmp->arg[i];
        tmp = tmp->next;
    }
}