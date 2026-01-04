#include "../../includes/minishell.h"

static int	handle_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(file, strerror(errno));
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error(file, strerror(errno));
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		print_error(file, strerror(errno));
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	setup_redirections(t_redir *redirs, t_data *data)
{
	t_redir	*tmp;
	int		ret;

	tmp = redirs;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIR_IN)
			ret = handle_redir_in(tmp->file);
		else if (tmp->type == TOKEN_REDIR_OUT)
			ret = handle_redir_out(tmp->file);
		else if (tmp->type == TOKEN_REDIR_APPEND)
			ret = handle_redir_append(tmp->file);
		else if (tmp->type == TOKEN_HEREDOC)
		{
			if (!handle_heredoc(tmp->file, data))
				return (-1);
		}
		if (ret == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
