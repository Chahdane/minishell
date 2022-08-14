# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 20:16:21 by owahdani          #+#    #+#              #
#    Updated: 2022/08/14 23:16:12 by owahdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DFLAGS = #-g -fsanitize=address
CFLAGS = -c -Wall -Wextra -Werror $(IFLAGS) $(DFLAGS)

IFLAGS = -Iincs/ -Ilibft/incs/ -I/Users/owahdani/homebrew/Cellar/readline/8.1.2/include/readline

LIBS = -lreadline -L/Users/owahdani/homebrew/Cellar/readline/8.1.2/lib -lft -L$(LIBFT_DIR)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = srcs/

SRC = error_handlers.c \
	  minishell.c \
	  helpers.c \
	  parsers.c \
	  parsers_2.c \
	  tokenizers.c \
	  tokenizers_2.c \
	  environment.c \
	  expansion.c \
	  expansion_2.c \
	  utils.c \
	  heredoc.c \
	  b_env.c \
	  b_export.c \
	  b_export2.c \
	  b_echo.c \
	  b_unset.c \
	  b_cd.c \
	  b_pwd.c \
	  b_exit.c \
	  execution.c \
	  builtin_ops.c \
	  file_handlers.c

SRC := $(addprefix $(SRC_DIR),$(SRC))
OBJ = $(patsubst $(SRC_DIR)%.c,%.o,$(SRC))

NAME = minishell

.PHONY: all clean fclean re

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(DFLAGS) $(LIBS) $(OBJ) -o $(NAME)

%.o: $(SRC_DIR)%.c incs/minishell.h
		$(CC) $(CFLAGS) $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) all

clean:
	rm -f $(OBJ) && make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
