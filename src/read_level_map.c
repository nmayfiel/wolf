#include "wolf.h"
#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

static int32_t	get_vals(t_level *level, char *line, t_mods *mods)
{
	char **vals;

	vals = ft_strsplit(line, ' ');
	if (str_array_size(vals) != 3)
		return (0);
	level->size_x = ft_atoi(vals[0]);
	level->size_y = ft_atoi(vals[1]);
	mods->player_angle = ft_atoi(vals[2]);
	ft_free_multi(4, vals[0], vals[1], vals[2], vals);
	level->size = level->size_x * level->size_y;
	level->map = (uint8_t *)malloc(sizeof(uint8_t) * level->size);
	return (1);
}

static int32_t	read_loop(t_level *level, char *line, t_mods *mods, t_uint2 *p)
{
	char **vals;

	p->x = 0;
	vals = ft_strsplit(line, ' ');
	while (vals[p->x] != NULL)
	{
		if (p->x + 1 > level->size_x)
			return (-1);
		level->map[p->x + (level->size_x * p->y)] = ft_atoi(vals[p->x]);
		free(vals[p->x]);
		if (level->map[p->x + (level->size_x * p->y)] & MAP_HERO)
		{
			mods->player_current_tile = p->x + (level->size_x * p->y);
			level->map[p->x + (level->size_x * p->y)] ^= MAP_HERO;
		}
		++p->x; 
	}
	ft_free_multi(2, vals, line);
	if (p->x != level->size_x)
		return (-1);
	++p->y;
	return (1);
}

int32_t	read_level_map(const char *fn, t_level *level, t_mods *mods)
{
     int fd;
     char *line;
     t_uint2 p;

     fd = open(fn, O_RDONLY);
     if (fd == -1)
	  return (-1);
     get_next_line(fd, &line);
     if (!get_vals(level, line, mods))
	     return (-1);
     free(line);
     p.y = 0;
     while (get_next_line(fd, &line) == 1)
	     if (read_loop(level, line, mods, &p) == -1)
		     return (-1);
     if (p.y != level->size_y)
	  return (-1);
     return (1);
}
