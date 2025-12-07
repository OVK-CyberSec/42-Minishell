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

typedef enum e_tokens
{
    cd,
    echo,
    env,
    export,
    unset,
    exit
}   t_tokens;

typedef struct s_command
{
    int nbr;
    char **arg;
    bool flag;
    char *tokens;
    int nbr_tokens;
    bool is_valid;
}   t_command;

typedef struct s_exit
{
    int id;
}   t_exit;

#endif