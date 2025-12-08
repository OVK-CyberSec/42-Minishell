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

#include "../includes/minishell.h"

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

int main(void)
{
    char *tests[] = {
		"echo hello world",
		"echo $USER",
		"cat < file.txt",
		"echo test > out.txt",
		"echo test >> out.txt",
		"cat << EOF",
		"ls -l | grep test",
		"cat file | grep test | wc -l",
		"echo 'hello world'",
		"echo \"hello $USER\"",
		"echo test>file",  // Sans espaces
		"cat<in>out",      // Multiple redirections
		NULL
    };
    int i = 0;
    while (tests[i])
    {
        printf("\n=== Test: %s ===\n", tests[i]);
        t_token *tokens = lexer(tests[i]);
        print_tokens(tokens);
		free_tokens(tokens);
        i++;
    }
    return (0);
}