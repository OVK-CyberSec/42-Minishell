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

// /* ========== ENVIRONNEMENT ========== */

// typedef struct s_env {
//     char            *key;       // Nom de la variable
//     char            *value;     // Valeur
//     struct s_env    *next; 
// } t_env;

/* ========== TOKENS ========== */

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,        // <
    TOKEN_REDIR_OUT,       // >
    TOKEN_REDIR_APPEND,    // >>
    TOKEN_HEREDOC,         // <<
    TOKEN_ENV_VAR          // $VAR
} t_token_type;

typedef struct s_token {
    t_token_type    type;
    char            *value;
    struct s_token  *next;
} t_token;

/* ========== REDIRECTIONS ========== */

typedef enum e_redir_type {
    REDIR_IN,      // <
    REDIR_OUT,     // >
    REDIR_APPEND,  // >>
    REDIR_HEREDOC  // <<
} t_redir_type;

typedef struct s_redir {
    t_redir_type    type;
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
    char    **env;      
    int         last_exit;      // Code de retour de la dernière commande ($?)
    bool        running;        // Flag pour la boucle principale
} t_shell;



/* ========== Build-in ========== */

int	builtin_cd(char **args, t_shell *shell);
int	builtin_echo(char **args);
void	builtin_env(t_shell *shell);
int	builtin_export(char **args, t_shell *shell);
int	builtin_pwd(t_shell *shell);
int	builtin_unset(char **argv, t_shell *shell);

/* ========== Exec ========== */

int exec_pipeline(char ***cmds, int nb_cmds, t_shell *shell);
int	exec_cmd(char **cmd, t_shell *shell);
bool	is_builtin(char *cmd);
void	exec_builtin(char **cmd, t_shell *shell);
int	exec_native(char **cmd, t_shell *shell, char **env);
void	exec_absolute(char **cmd, char **env, t_shell *shell);
char	*get_path(char *cmd, char **env);

/* ========== Tools ========== */

//char *get_env_value(t_shell shell, char *val);
//void    update_env_value(t_shell shell, char *val);
int is_valid_identifier(const char *var);
void *sort_tab(char **env);
void update_env_value(t_shell *shell, const char *key, const char *value);
char	*get_env_value(char **env, const char *key);
void free_tab(char **tab);
void	mark_as_exported(t_shell *shell, char *key);
//t_env *copy_env_list(t_env *env);
//void free_env_list(t_env *env);

#endif

