/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:33:16 by mohifdi           #+#    #+#             */
/*   Updated: 2026/01/13 19:33:17 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include "../Libft/libft.h"

/* Token Types */
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_APPEND 5
# define TOKEN_HEREDOC 6

/* Exit Codes */
# define SUCCESS 0
# define FAILURE 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

/* Structures */
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipex
{
	int		n;
	int		i;
	int		**pipes;
	pid_t	*pids;
}	t_pipex;

typedef struct s_data
{
	t_env			*env;
	t_cmd			*cmds;
	char			*input;
	int				exit_status;
	int				in_heredoc;
}	t_data;

extern int	g_signal;

/* Parsing Functions */
t_token		*lexer(char *input);
t_cmd		*parser(t_token *tokens);
void		expand_variables(t_token **tokens, t_data *data);
char		*get_env_value(t_env *env, char *key);
void		fill_cmd_args(t_cmd *cmd, t_token **tokens);
t_token		*create_token(char *value, int type);
void		add_token(t_token **tokens, t_token *new_token);
int			get_token_type(char *str);

/* Execution Functions */
void		execute_commands(t_cmd *cmds, t_data *data);
void		execute_single_cmd(t_cmd *cmd, t_data *data);
void		execute_pipeline(t_cmd *cmds, t_data *data);
int			setup_redirections(t_redir *redirs, t_data *data);
void		setup_pipes(t_pipex *px);
void		exec_binary(t_cmd *cmd, t_data *data);
int			count_cmds(t_cmd *cmds);
void		wait_all_pids(t_pipex *px, int *status);
void		close_all_pipes(t_pipex *px);
/* Built-in Commands */
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd, t_data *data);
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_data *data);
int			builtin_pwd(t_data *data);
int			builtin_export(char **args, t_data *data);
int			builtin_unset(char **args, t_data *data);
int			builtin_env(t_data *data);
int			builtin_exit(char **args, t_data *data);

/* Environment Functions */
t_env		*init_env(char **envp);
void		add_env_var(t_env **env, char *key, char *value);
void		remove_env_var(t_env **env, char *key);
char		**env_to_array(t_env *env);
void		free_env(t_env *env);

/* Signal Handling */
void		setup_signals(void);
void		signal_handler(int signum);
void		setup_heredoc_signals(void);
void		setup_heredoc_signals(void);

/* Heredoc Functions */
char		*handle_heredoc(char *delimiter, t_data *data);
void		process_heredoc(t_redir *redir, t_data *data);
char		*handle_heredoc(char *delimiter, t_data *data);
void		heredoc_signal_handler(int signum);

/* Path Resolution */
char		*find_command_path(char *cmd, t_env *env);
int			is_directory(char *path);

/* Memory Management */
void		free_tokens(t_token *tokens);
void		free_commands(t_cmd *cmds);
void		free_redirections(t_redir *redirs);
void		free_split(char **split);
void		cleanup_data(t_data *data);

/* Utility Functions */
int			ft_isspace(int c);
int			is_valid_id(const char *s);
char		*expand_exit_status(int exit_status);
int			env_key_exists(t_env **env, char *key);

/* Error Handling */
void		print_error(char *cmd, char *msg);
void		exit_error(char *msg, int code);

/* Input Validation */
int			check_syntax(t_token *tokens);
int			check_quotes(char *input);

#endif
