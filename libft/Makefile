# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: owahdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 13:39:42 by owahdani          #+#    #+#              #
#    Updated: 2022/01/31 21:37:03 by owahdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

IFLAGS = -Iincs

CFLAGS = -Wall -Wextra -Werror -c $(IFLAGS)

SRC_BASE = srcs
OBJ_BASE = objs

SUB_SRC :=	ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_tolower.c 
SRC := $(addprefix characters/,$(SUB_SRC))

SUB_SRC := 	get_next_line.c \
		get_next_line_utils.c
SUB_SRC :=	$(addprefix get_next_line/,$(SUB_SRC)) \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c
SRC += $(addprefix file_handling/,$(SUB_SRC))

SUB_SRC := 	decimals.c \
		flags.c \
		ft_printf.c \
		hex.c \
		parsers.c \
		strings.c
SRC += $(addprefix ft_printf/,$(SUB_SRC))

SUB_SRC :=	ft_bzero.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_calloc.c \
		ft_memcmp.c \
		ft_memmove.c
SRC += $(addprefix memory/,$(SUB_SRC))

SUB_SRC :=	ft_lstadd_back.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstsize.c \
		ft_lstadd_front.c \
		ft_lstdelone.c \
		ft_lstlast.c \
		ft_lstnew.c
SRC += $(addprefix lists/,$(SUB_SRC))

SUB_SRC :=	ft_atoi.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strnstr.c \
		ft_itoa.c \
		ft_striteri.c \
		ft_strlen.c \
		ft_strrchr.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strncmp.c \
		ft_substr.c \
		ft_strtoi.c
SRC += $(addprefix strings/,$(SUB_SRC))

SRC := $(addprefix $(SRC_BASE)/,$(SRC))
OBJ := $(patsubst $(SRC_BASE)%.c,$(OBJ_BASE)%.o,$(SRC))

OBJ_DIRS := $(sort $(dir $(OBJ)))

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJ)
	ar -rc $(NAME) $(OBJ)

$(OBJ_BASE)/%.o: $(SRC_BASE)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIRS):
	mkdir -p $@

clean:
	rm -fr $(OBJ_BASE)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
