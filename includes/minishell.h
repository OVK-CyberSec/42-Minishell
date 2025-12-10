#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ========== ENVIRONNEMENT ========== */

typedef struct s_env {
    char            *key;       // Nom de la variable
    char            *value;     // Valeur
    struct s_env    *next;      // Liste chaînée
} t_env;

/* ========== TOKENS ========== */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	TOKEN_VAR,
}	t_token_type;

typedef struct s_token {
    t_token_type    type;
    char            *value;
    int				in_quotes;
    struct s_token  *next;
} t_token;

typedef struct s_redir {
    t_token_type    type;
    char            *file;         // Nom du fichier ou délimiteur heredoc
    int             fd;            // File descriptor (utile pour heredoc temporaire)
    struct s_redir  *next;
} t_redir;

/* ========== COMMANDE SIMPLE ========== */

typedef struct s_cmd {
    char    **args;         // Tableau d'arguments terminé par NULL
    t_redir *redirs;        // Liste chaînée de redirections
    int     argc;           // Nombre d'arguments (optionnel mais pratique)
} t_cmd;

/* ========== PIPELINE ========== */

typedef struct s_pipeline {
    t_cmd   **commands;     // Tableau de commandes
    int     cmd_count;      // Nombre de commandes
} t_pipeline;

/* ========== CONTEXTE GLOBAL ========== */

typedef struct s_shell {
    t_env       *env_list;      // ✓ Liste chaînée (au lieu de char**)
    int         last_exit;      // Code de retour de la dernière commande ($?)
    bool        running;        // Flag pour la boucle principale
} t_shell;

/* ========== PARSER ========== */

t_cmd	*parser(t_token *tokens);
t_cmd	*init_cmd(void);
t_token	*handle_redirection(t_cmd *cmd, t_token *token);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
int		is_redirection(t_token_type type);
void	print_one_redir(t_redir *redir);

/* ========== PARSER UTILS ========== */

void	free_cmds(t_cmd *cmds);

/* ========== DEBUG ========== */

void	print_cmds(t_cmd *cmds);
#endif