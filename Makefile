# Standard
NAME				= Minishell

# Directories
LIBFT				= ./Libft/libft.a
INC					= .
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f

BUILTIN_DIR		=		$(SRC_DIR)builtins/env.c \
						$(SRC_DIR)builtins/cd.c \
						$(SRC_DIR)builtins/pwd.c \
 						$(SRC_DIR)builtins/echo.c \
						$(SRC_DIR)builtins/unset.c \
 						$(SRC_DIR)builtins/export.c \
 						$(SRC_DIR)builtins/exit.c \

DATA_DIR		=		$(SRC_DIR)data/init.c \
						$(SRC_DIR)data/init2.c \
						$(SRC_DIR)data/cleaner.c \

PARSING_DIR		=		$(SRC_DIR)parsing/expander.c \
						$(SRC_DIR)parsing/lexer.c \
						$(SRC_DIR)parsing/validation.c \
						$(SRC_DIR)parsing/parser.c \
						$(SRC_DIR)parsing/parser2.c \
						$(SRC_DIR)parsing/tokenizer.c \

SIGNAL_DIR		=		$(SRC_DIR)signals/signals.c \

EXEC_DIR		=		$(SRC_DIR)exec/exec.c \
 						$(SRC_DIR)exec/exec2.c \
						$(SRC_DIR)exec/exec3.c \
						$(SRC_DIR)exec/path.c	\

UTILS_DIR		=		$(SRC_DIR)utils/errors.c \
						$(SRC_DIR)utils/utils.c \
						$(SRC_DIR)utils/redirections.c \
						$(SRC_DIR)utils/heredoc.c \

MAIN			=		$(SRC_DIR)main.c
# Concatenate all source files
SRCS 		=		 $(BUILTIN_DIR) $(DATA_DIR) $(PARSING_DIR) \
       				 $(EXEC_DIR) $(SIGNAL_DIR) $(UTILS_DIR) $(MAIN)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					@make all

$(LIBFT):
					@make -C ./Libft

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./Libft

fclean: 	clean
			@$(RM) $(NAME)
			@make fclean -C ./Libft


re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re