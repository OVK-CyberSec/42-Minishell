
# Minishell
This project has been created as part of the 42 curriculum by mohifdi and mnakasto

## Description

Minishell is a simple Unix shell implementation that recreates the basic functionality of bash. This project provides hands-on experience with process management, file descriptors, pipes, and system calls in C. The shell interprets commands, manages environment variables, handles redirections, and executes pipelines—all fundamental concepts in Unix-like operating systems.

### Instructions

- **Command execution** with PATH resolution
- **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipelines**: Chain multiple commands with `|`
- **Redirections**: Input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)
- **Environment variables**: Expansion of `$VAR` and `$?`
- **Signal handling**: Proper handling of `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`
- **Quote handling**: Single (`'`) and double (`"`) quotes
- **Interactive prompt** with command history using GNU Readline

### Prerequisites

- GCC compiler
- GNU Readline library
- Make

### Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd 42-Minishell
```

2. Install the Readline library (if not already installed):
```bash
sudo apt-get install libreadline-dev
```

3. Compile the project:
```bash
make
```

This will create the `minishell` executable.

### Compilation Options

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile the entire project
```

### Execution

Run the shell:
```bash
./minishell
```

## Resources

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Unix System Calls](https://man7.org/linux/man-pages/man2/syscalls.2.html)
- [Process Management in Unix](https://www.tutorialspoint.com/unix/unix-processes.htm)

## License

This project is part of the 42 School curriculum and is intended for educational purposes.
