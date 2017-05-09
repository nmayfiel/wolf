# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/09 01:59:55 by nmayfiel          #+#    #+#              #
#    Updated: 2017/05/09 02:27:02 by nmayfiel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft/ -Lminilibx
LDLIBS = -lft -lmlx -framework OpenGL -framework AppKit -framework OpenCL
CFLAGS += -Iinclude/ -Ilibft/include/ -Iminilibx

FILENAMES = main.c draw.c loop.c render.c splash.c
FNS = $(addprefix src/, $(FILENAMES))
OBJECTS = $(addprefix build/, $(FILENAMES:.c=.o))

CLC = /System/Library/Frameworks/OpenCL.framework/Libraries/openclc
CLC_FLAGS = -emit-llvm -c -arch gpu_64 -Wall

all: $(NAME)

libft/libft.a:
	cd libft && make

minilibx/libmlx.a:
	cd minilibx && make

kernel/kernel.bc:
	cd kernel && $(CLC) $(CLC_FLAGS) kernel_x86_64.cl -o kernel.bc

$(NAME): $(OBJECTS) minilibx/libmlx.a libft/libft.a kernel/kernel.bc
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
	/bin/rm -f kernel/kernel.bc
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
