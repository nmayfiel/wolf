/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 14:46:36 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/14 01:34:32 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
** read_until_newline is a recursive helper that fills line string with
** the characters up to, but not including the first newline it finds
** it fills the overflow, or null if there isn't one
** finally, returns 1 on success, 0 on fail, -1 on error
*/

static int		read_until_newline(const int fd, char **line, char **overflow)
{
	int		num_read;
	char	buf[BUFF_SIZE + 1];
	char	*cat_str;

	if ((num_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[num_read] = '\0';
		if (ft_strchr(buf, '\n') != NULL)
		{
			cat_str = ft_strndup(buf, ft_strchr(buf, '\n') - buf);
			*overflow = ft_strdup(ft_strchr(buf, '\n') + 1);
		}
		else
			cat_str = ft_strdup(buf);
		*line = ft_mallocat(*line, cat_str);
		free(cat_str);
		if (ft_strchr(buf, '\n') == NULL && num_read == BUFF_SIZE)
			return (read_until_newline(fd, line, overflow));
		return (1);
	}
	if (num_read < 0)
		return (-1);
	if (*line)
		return (1);
	return (0);
}

/*
** get_fh checks if the file handle struct exists
** on the heap, if not, mallocs it, then fills it
** with default values
** if it does exist, checks whether the current fd
** has been opened before, if not saves it
** returns the index for the current fd
*/

static int		get_fh(t_fh *fhs, const int fd)
{
	int		i;

	if (fhs->num_fds == 0)
	{
		fhs->fds = (int *)malloc(sizeof(int));
		fhs->fds[0] = fd;
		fhs->overs = (char **)malloc(sizeof(char *));
		fhs->overs[0] = NULL;
		fhs->num_fds = 1;
		return (0);
	}
	i = -1;
	while (++i < fhs->num_fds)
		if (fhs->fds[i] == fd)
			return (i);
	fhs->fds = ft_realloc(fhs->fds, sizeof(int) * i,
			sizeof(int) * (i + 1));
	fhs->overs = ft_realloc(fhs->overs, sizeof(char *) * i,
			sizeof(char *) * (i + 1));
	fhs->fds[i] = fd;
	fhs->overs[i] = NULL;
	fhs->num_fds++;
	return (i);
}

static char		*set_line(char *lstr, char **overflow, char *ostr, char **tmp)
{
	char *line;

	line = lstr;
	free(*overflow);
	*overflow = ostr;
	free(*tmp);
	return (line);
}

/*
** Perform necessary checks and setup
** the initial variables before getting the next line
*/

static int		setup_gnl(char **line, int *fi, t_fh *fhs, const int fd)
{
	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	*fi = get_fh(fhs, fd);
	return (0);
}

/*
** get_next_line takes a file descriptor and a pointer to a string
** then fills string with the characters before the next newline
** in the file
*/

int				get_next_line(const int fd, char **line)
{
	static t_fh		fhs;
	int				fi;
	char			*tmp;

	if (setup_gnl(line, &fi, &fhs, fd) != 0)
		return (-1);
	tmp = fhs.overs[fi] ? ft_strdup(fhs.overs[fi]) : NULL;
	if (tmp && *tmp == '\n')
	{
		*line = set_line(ft_strdup("\0"), &fhs.overs[fi],
				ft_strdup(tmp + 1), &tmp);
		return (1);
	}
	else if (tmp && ft_strchr(tmp, '\n') != NULL)
	{
		*line = set_line(ft_strndup(tmp, ft_strchr(tmp, '\n') - tmp),
				&fhs.overs[fi], ft_strdup(ft_strchr(tmp, '\n') + 1), &tmp);
		return (1);
	}
	else if (tmp && *tmp != '\0')
		*line = set_line(ft_strdup(fhs.overs[fi]), &fhs.overs[fi], NULL, &tmp);
	else if (tmp != NULL)
		ft_free_multi(2, tmp, fhs.overs[fi]);
	return (read_until_newline(fd, line, &fhs.overs[fi]));
}
