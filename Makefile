# Standard
NAME				= Minishell

# Directories
LIBFT				= ./Libft/libft.a
INC					= .
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall  -Wextra -I
RM					= rm -f

BUILTIN_DIR		=		$(SRC_DIR)built-in/env.c \
						$(SRC_DIR)built-in/cd.c \
						$(SRC_DIR)built-in/pwd.c \
 						$(SRC_DIR)built-in/echo.c \
						$(SRC_DIR)built-in/unset.c \
# 						$(SRC_DIR)built-in/export.c \
# 						$(SRC_DIR)built-in/exit.c \


# DATA_DIR		=		$(SRC_DIR)data/init.c \

# LEXER_DIR		=		$(SRC_DIR)lexer/cd.c \

# PARSING_DIR		=		$(SRC_DIR)parsing/cd.c \

EXEC_DIR		=		$(SRC_DIR)exec/exec_tools.c \
 						$(SRC_DIR)exec/exec.c \
						$(SRC_DIR)exec/exec_pipeline.c	\

UTILS_DIR		=		$(SRC_DIR)utils/tools.c \
						$(SRC_DIR)utils/tools2.c \

MAIN			=		$(SRC_DIR)main.c
# Concatenate all source files
SRCS 				= $(BUILTIN_DIR) $(DATA_DIR) $(LEXER_DIR) $(PARSING_DIR) $(EXEC_DIR) $(UTILS_DIR) $(MAIN)

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

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)

re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re