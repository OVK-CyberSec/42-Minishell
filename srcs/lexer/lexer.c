#include "../../includes/minishell.h"

t_token *lexer(char *input)
{
    t_token *tokens = NULL;
    int i = 0;
    
    while (input[i])
    {
        if (is_space(input[i]))
            i++;
        else if (input[i] == '|')
            ajouter_token(&tokens, TOKEN_PIPE, "|"), i++;
        else if (input[i] == '\'' || input[i] == '"')
            i = gerer_quotes(input, i, &tokens);
        else if (input[i] == '<' || input[i] == '>')
            i = gerer_redirections(input, i, &tokens);
        else
            i = gerer_mot(input, i, &tokens);
    }
    return tokens;
}