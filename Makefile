NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

LIB = $(LIBFT) -lreadline

SRC = test_executor.c \
		builtin.c \
		builtin_strict.c \
		execute.c \
		exit_status.c \
		find_cmd.c \
		print_error.c \
		util.c
		
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re libft

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)
	@echo "<$(NAME)> is available."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@echo "Removed $(NAME) object files."

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "Removed $(NAME)."

re: fclean all