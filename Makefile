# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: owahdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 20:16:21 by owahdani          #+#    #+#              #
#    Updated: 2022/07/25 18:31:28 by owahdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DFLAGS = -g -fsanitize=address
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
	  tokenizers.c \
	  tokenizers_2.c

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
