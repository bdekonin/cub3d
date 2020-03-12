/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_filepath.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 09:33:38 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:36:18 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static int read_valid_image(int fd)
{
	char buf[10];
	int ret;

	if (read(fd, buf, 10) < 0)
		return (-1);
	if (!ft_strnstr(buf, "PNG", 10) && !ft_strnstr(buf, "XPM", 10))
		return (0);
	return (1);
}

char *read_filepath(char *line)
{
	int		fd;
	char	*path;

	if (*line != ' ')
		return ("file");
	while (*line == ' ')
		line++;
	path = ft_substr(line, 0, ft_strlen_nospace(line));
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return ("file");
	}
	if (!read_valid_image(fd))
	{
		close(fd);
		free(path);
		return ("file");
	}
	close (fd);
	return (path);
}
