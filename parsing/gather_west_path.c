/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_west_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/02 17:20:29 by bdekonin      ########   odam.nl         */
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

static char		*read_west_path(char *line)
{
	int		fd;
	char	*path;

	while (*line == ' ' || *line == 'W' || *line == 'E')
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

int				get_west(char *line, t_data *data)
{
	if (data->malloced[3] == 'Y')
	{
		return (ft_puterror("get_west | multiple elements found."));
	}
	data->west_path = read_west_path(line);
	if (!data->west_path)
	{
		return (ft_puterror("get_west | malloc failed."));
	}
	else if (ft_strncmp(data->west_path, "file", 100) == 0)
	{
		return (ft_puterror("get_west | file could not be opened / found."));
	}
	data->malloced[3] = 'Y';
	return (1);
}
