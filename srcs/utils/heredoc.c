#include "../../includes/minishell.h"

static char	*read_heredoc_lines(char *delimiter, int pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_signal)
		{
			if (g_signal)
				return (NULL);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
	return (ft_strdup("done"));
}

char	*handle_heredoc(char *delimiter, t_data *data)
{
	int		pipe_fd[2];
	char	*content;

	if (pipe(pipe_fd) == -1)
		return (NULL);
	setup_heredoc_signals();
	content = read_heredoc_lines(delimiter, pipe_fd[1]);
	close(pipe_fd[1]);
	if (!content || g_signal)
	{
		close(pipe_fd[0]);
		setup_signals();
		return (NULL);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	setup_signals();
	(void)data;
	free(content);
	return (ft_strdup("heredoc_done"));
}
