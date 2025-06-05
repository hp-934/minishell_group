# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 13:03:32 by yaepark           #+#    #+#              #
#    Updated: 2025/06/02 14:25:43 by yaepark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

LIB = $(LIBFT) -lreadline

SRC =	builtin.c \
		builtin_strict.c \
		env.c \
		env_convert.c \
		env_node.c \
		execute.c \
		find_cmd.c \
		print_error.c \
		util1.c	\
		util2.c \
		parser.c utils.c check_syntax.c write_error.c count_args.c exit_status.c \
		count_commands.c spaces.c quotes_variables.c redirection.c redirection1.c\
		main.c

OBJ = $(SRC:.c=.o)

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

.PHONY: all clean fclean re libft