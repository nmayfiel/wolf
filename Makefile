NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft/ -Lminilibx
LDLIBS = -lft -lmlx -framework OpenGL -framework AppKit
CFLAGS += -Iinclude/ -Ilibft/include/ -Iminilibx

FILENAMES = main.c draw.c loop.c render.c splash.c keys.c
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
