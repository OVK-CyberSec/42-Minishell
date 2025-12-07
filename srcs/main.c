
#include "../includes/minishell.h"


int main(int ac, char **av, char **env)
{
    char *input;
    
    (void)ac;
    (void)av;
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        free(input);
    }
    return (0);
}