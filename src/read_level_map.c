#include "wolf.h"
#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

size_t get_char_array_size(char **arr)
{
     size_t i;

     i = 0;
     while (arr[i] != NULL)
	  ++i;
     return (i);
}

void debug_print_map_values(uint8_t *map, uint32_t size, uint32_t size_x)
{
     uint32_t i;

     i = 0;
     while (i < size)
     {
	  ft_putnbr(map[i]);
	  ft_putchar(' ');
	  if ((i + 1) % size_x == 0)
	       ft_putchar('\n');
	  ++i;
     }
     ft_putchar('\n');
}

int32_t read_level_map(const char *fn, t_level *level, t_mods *mods)
{
     int fd;
     char *line;
     char **vals;
     uint32_t x;
     uint32_t y;

     fd = open(fn, O_RDONLY);
     if (fd == -1)
	  return (-1);
     get_next_line(fd, &line);
     vals = ft_strsplit(line, ' ');
     if (get_char_array_size(vals) != 2)
	  return (-1);
     level->size_x = ft_atoi(vals[0]);
     level->size_y = ft_atoi(vals[1]);
     free(line);
     free(vals[0]);
     free(vals[1]);
     free(vals);
     level->size = level->size_x * level->size_y;
     level->map = (uint8_t *)malloc(sizeof(uint8_t) * level->size);
     y = 0;
     while (get_next_line(fd, &line) == 1)
     {
	  x = 0;
	  vals = ft_strsplit(line, ' ');
	  while (vals[x] != NULL)
	  {
	       if (x + 1 > level->size_x)
		    return (-1);
	       level->map[x + (level->size_x * y)] = ft_atoi(vals[x]);
	       free(vals[x]);
	       if (level->map[x + (level->size_x * y)] & MAP_HERO)
	       {
		    mods->player_current_tile = x + (level->size_x * y);
		    level->map[x + (level->size_x * y)] ^= MAP_HERO;
	       }
	       ++x; 
	  }
	  free(vals);
	  free(line);
	  if (x != level->size_x)
	       return (-1);
	  ++y;
     }
     if (y != level->size_y)
	  return (-1);
     //debug_print_map_values(level->map, level->size, level->size_x);
     return (1);
}
