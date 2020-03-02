/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_east_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/02 17:19:03 by bdekonin      ########   odam.nl         */
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

static char		*read_east_path(char *line)
{
	int		fd;
	char	*path;

	while (*line == ' ' || *line == 'E' || *line == 'A')
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
	close(fd);
	return (path);
}

int				get_east(char *line, t_data *data)
{
	if (data->malloced[2] == 'Y')
	{
		return (ft_puterror("get_east | multiple elements found."));
	}
	data->east_path = read_east_path(line);
	if (!data->east_path)
	{
		return (ft_puterror("get_east | malloc failed."));
	}
	else if (ft_strncmp(data->east_path, "file", 100) == 0)
	{
		return (ft_puterror("get_east | file could not be opened / found."));
	}
	data->malloced[2] = 'Y';
	return (1);
}
