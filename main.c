/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnakasto <mnakasto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:34:42 by mnakasto          #+#    #+#             */
/*   Updated: 2025/12/08 20:14:51 by mnakasto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int main(int ac, char **av, char **env)
// {
//     char *input;
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 			break;
// 		lexer(input);
// 		if (*input)
// 			add_history(input);
// 		printf("You typed the following: %s\n", input);
// 		free(input);
// 	}
// 	return 0;
// }

int main(int ac, char **av, char **envp)
{
    char    *input;
    t_token *tokens;
    t_cmd   *cmds;
    
    (void)ac;
    (void)av;
    (void)envp;
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (!*input)
        {
            free(input);
            continue;
        }
        add_history(input);
        
        // === LEXER ===
        tokens = lexer(input);
        if (!tokens)
        {
            printf("❌ Erreur lexer\n");
            free(input);
            continue;
        }
        
        printf("\n📊 TOKENS:\n");
        print_tokens(tokens);
        
        // === PARSER ===
        cmds = parser(tokens);
        if (!cmds)
        {
            printf("❌ Erreur parser\n");
            free_tokens(tokens);
            free(input);
            continue;
        }
        
        printf("\n📦 COMMANDES:");
        print_cmds(cmds);
        printf("\n");
        
        // === CLEANUP ===
        free_tokens(tokens);
        free_cmds(cmds);
        free(input);
    }
    
    return (0);
}
