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

extern char **environ;
# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"


typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ENV_VAR
} t_token_type;

typedef struct s_token {
    t_token_type    type;
    char            *value;
    struct s_token  *next;
} t_token;


typedef struct s_cmd {
    char **args;           // Tableau d'arguments
    char *input_file;      // Fichier de redirection 
    char *output_file;     // Fichier de redirection >
    int append;            // Mode append pour >>
    char *heredoc_delim;   // Délimiteur pour 
} t_cmd;

typedef struct s_pipeline {
    t_cmd **commands;      // Tableau de commandes
    int cmd_count;         // Nombre de commandes
} t_pipeline;

#endif