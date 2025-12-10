#include "../../includes/minishell.h"

int builtin_pwd(t_shell *shell)
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        shell->last_exit = 0;
        return (0);
    }
    return (1);
}