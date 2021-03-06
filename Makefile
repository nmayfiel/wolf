# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/09 01:59:55 by nmayfiel          #+#    #+#              #
#    Updated: 2017/08/10 00:27:37 by nmayfiel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft/ -Lminilibx
LDLIBS = -lft -lmlx -framework OpenGL -framework AppKit
CFLAGS += -Iinclude/ -Ilibft/include/ -Iminilibx

FILENAMES = main.c draw.c loop.c render.c splash.c images.c handle_input.c \
		errors.c read_level_map.c keys.c mouse.c clock.c helpers.c
FNS = $(addprefix src/, $(FILENAMES))
OBJECTS = $(addprefix build/, $(FILENAMES:.c=.o))

all: $(NAME)

libft/libft.a:
	cd libft && make

minilibx/libmlx.a:
	cd minilibx && make

$(NAME): $(OBJECTS) minilibx/libmlx.a libft/libft.a
	$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) $(OBJECTS)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -o $@ -c $<

build:
	mkdir build/

clean:
	/bin/rm -rf build/

fclean: clean
	cd libft && make fclean
	cd minilibx && make clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
