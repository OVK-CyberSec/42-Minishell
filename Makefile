NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a


SRCS = main.c srcs/lexer/token_handler.c srcs/lexer/token_reader.c \
		srcs/utils/tools.c srcs/parser/parser.c srcs/utils/parser_utils.c \
		srcs/utils/print_utils.c srcs/utils/tools2.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re