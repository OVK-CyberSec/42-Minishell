#include "../../includes/minishell.h"

void env_print(t_env *env_list, t_shell *shell)
{
    t_env *current;
    
    current = env_list;
    while (current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    shell->last_exit = 0;
}