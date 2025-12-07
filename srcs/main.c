
#include "../includes/minishell.h"


int main(int ac, char **av, char **env)
{
    char *input;
    t_token *tokens;

    (void)ac;
    (void)av;
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        tokens = lexer(line);
        free(input);
    }
    return (0);
}