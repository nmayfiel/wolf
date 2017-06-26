# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 13:39:55 by nmayfiel          #+#    #+#              #
#    Updated: 2017/06/14 01:30:16 by nmayfiel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -Iinclude/
SRC  =	ft_putchar_fd.c ft_putchar.c ft_putstr_fd.c ft_putstr.c				\
		ft_putendl_fd.c ft_putendl.c ft_putnbr_fd.c ft_putnbr.c				\
		ft_memset.c ft_bzero.c ft_isalpha.c ft_isdigit.c ft_isalnum.c		\
		ft_isascii.c ft_isprint.c ft_tolower.c ft_toupper.c ft_strcpy.c		\
		ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlen.c ft_strlcat.c		\
		ft_strchr.c ft_strrchr.c ft_atoi.c ft_itoa.c ft_strstr.c			\
		ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_memalloc.c ft_memdel.c 	\
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c		\
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c		\
		ft_strjoin.c ft_strsub.c ft_strsplit.c ft_lstnew.c ft_lstadd.c		\
		ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c		\
		ft_lstdelone.c ft_lstdel.c ft_lstiter.c ft_lstmap.c ft_strdup.c		\
		ft_strtrim.c														\
		ft_isupper.c ft_islower.c ft_strlcpy.c ft_isspace.c ft_numlen.c 	\
		ft_abs.c ft_strcasestr.c ft_charequ_ci.c ft_memcpyr.c ft_strndup.c	\
		ft_realloc.c ft_itoa_base.c ft_print_memory.c ft_mallocat.c			\
		ft_swap.c get_next_line.c ft_free_multi.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
