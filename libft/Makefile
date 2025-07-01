# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roo <roo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 11:13:01 by rocfemia          #+#    #+#              #
#    Updated: 2025/03/20 00:47:21 by roo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_substr.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strtrim.c \
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_atoi.c ft_calloc.c ft_memmove.c  ft_strjoin.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_split.c ft_itoa.c\
	ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c\
	ft_lstadd_front.c ft_lstadd_back.c ft_lstlast.c ft_lstnew.c ft_lstsize.c\
	ft_printf.c ft_printf_utils.c ft_libft_utils.c\
	get_next_line.c get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re