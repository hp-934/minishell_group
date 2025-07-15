# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 13:03:32 by yaepark           #+#    #+#              #
#    Updated: 2025/06/23 21:17:56 by yaepark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

LIB = $(LIBFT) -lreadline

SRC =	builtin_all.c \
		builtin_cd.c \
		builtin_error.c \
		builtin_exit.c \
		builtin_export.c \
		builtin_others.c \
		check_syntax1.c \
		check_syntax2.c \
		count_args.c \
		count_commands.c \
		env.c \
		env_convert.c \
		env_node.c \
		execute1.c \
		execute2.c \
		exit_status.c \
		find_cmd.c \
		heredoc.c \
		print_error.c \
		signal1.c \
		signal2.c \
		util1.c	\
		util3.c \
		util4.c \
		parser.c \
		tokenize.c \
		redirection1.c \
		redirection2.c\
		redirection3.c\
		spaces.c \
		quotes_variables1.c \
		quotes_variables2.c \
		main_mstest.c

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