#include "../../includes/minishell.h"

static void exec_child_process(
    char **cmd,
    t_shell *shell,
    int prev_read_fd,
    int fd[2],
    int is_last)
{
    if (prev_read_fd != -1)
    {
        dup2(prev_read_fd, STDIN_FILENO);
        close(prev_read_fd);
    }
    if (!is_last)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    exec_cmd(cmd, shell);
    exit(shell->last_exit);
}

static pid_t create_pipe_and_fork(int i, int nb_cmds, int fd[2])
{
    if (i < nb_cmds - 1 && pipe(fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    return (fork());
}

static void parent_cleanup(int *prev_read_fd, int fd[2], int is_last)
{
    if (*prev_read_fd != -1)
        close(*prev_read_fd);
    if (!is_last)
    {
        close(fd[1]);
        *prev_read_fd = fd[0];
    }
}

int exec_pipeline(char ***cmds, int nb_cmds, t_shell *shell)
{
    int     i;
    int     fd[2];
    int     prev_read_fd;
    pid_t   pid;

    prev_read_fd = -1;
    i = 0;
    while (i < nb_cmds)
    {
        pid = create_pipe_and_fork(i, nb_cmds, fd);
        if (pid == -1)
            return (1);
        if (pid == 0)
            exec_child_process(cmds[i], shell,
                prev_read_fd, fd, i == nb_cmds - 1);
        parent_cleanup(&prev_read_fd, fd, i == nb_cmds - 1);
        i++;
    }
    while (wait(&shell->last_exit) > 0)
        ;
    return (0);
}
