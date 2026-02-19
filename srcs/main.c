/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:38:22 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:38:23 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	init_data(t_data *data, char **envp)
{
	data->env = init_env(envp);
	data->cmds = NULL;
	data->input = NULL;
	data->exit_status = 0;
	data->in_heredoc = 0;
}

static int	handle_parsing(char *input, t_data *data, t_token **tokens)
{
	if (!check_quotes(input))
	{
		print_error("minishell", "unclosed quotes");
		data->exit_status = 2;
		return (0);
	}
	*tokens = lexer(input);
	if (!*tokens)
		return (0);
	if (!check_syntax(*tokens))
	{
		print_error("minishell", "syntax error");
		data->exit_status = 2;
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}

void	process_input(char *input, t_data *data)
{
	t_token	*tokens;

	if (!input || !*input)
		return ;
	add_history(input);
	if (!handle_parsing(input, data, &tokens))
		return ;
	expand_variables(&tokens, data);
	data->cmds = parser(tokens);
	free_tokens(tokens);
	if (data->cmds)
	{
		execute_commands(data->cmds, data);
		free_commands(data->cmds);
		data->cmds = NULL;
	}
}

static int	read_loop(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (g_signal)
	{
		data->exit_status = 130;
		g_signal = 0;
	}
	process_input(input, data);
	free(input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data, envp);
	setup_signals();
	while (read_loop(&data))
		;
	cleanup_data(&data);
	return (data.exit_status);
}
