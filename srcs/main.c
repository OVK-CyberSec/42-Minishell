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

void	process_input(char *input, t_data *data)
{
	t_token	*tokens;

	if (!input || !*input)
		return ;
	add_history(input);
	if (!check_quotes(input))
	{
		print_error("minishell", "unclosed quotes");
		data->exit_status = 2;
		return ;
	}
	tokens = lexer(input);
	if (!tokens)
		return ;
	if (!check_syntax(tokens))
	{
		print_error("minishell", "syntax error");
		data->exit_status = 2;
		free_tokens(tokens);
		return ;
	}
	expand_variables(tokens, data);
	data->cmds = parser(tokens);
	free_tokens(tokens);
	if (data->cmds)
	{
		execute_commands(data->cmds, data);
		free_commands(data->cmds);
		data->cmds = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argc;
	(void)argv;
	init_data(&data, envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal)
		{
			data.exit_status = 130;
			g_signal = 0;
		}
		process_input(input, &data);
		free(input);
	}
	cleanup_data(&data);
	return (data.exit_status);
}