# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: owahdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 20:16:21 by owahdani          #+#    #+#              #
#    Updated: 2022/07/19 20:54:59 by owahdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -c -Wall -Wextra -Werror $(IFLAGS)

IFLAGS = -Iincs/ -I/Users/owahdani/homebrew/Cellar/readline/8.1.2/include/readline

LIBS = -lreadline -L/Users/owahdani/homebrew/Cellar/readline/8.1.2/lib 

SRC_DIR = srcs/

SRC = 

SRC := $(addprefix $(SRC_DIR),$(SRC))
OBJ = $(patsubst $(SRC_DIR)%.c,%.o,$(SRC))

NAME = minishell

.PHONY: all clean fclean re

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: $(SRC_DIR)%.c incs/minishell.h
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
