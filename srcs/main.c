
#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char *read;
    while (1)
    {
        read = readline("minishell> ");
        if (!read)
            // free and exit properly
        if (empty_line(read))
            continue ;
        if (!parse_content())
            continue;
        if (!exec())
            continue;
        
    }
    return 0;
}