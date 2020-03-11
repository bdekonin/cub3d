/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_sprite_path.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:21:47 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 11:05:33 by bdekonin      ########   odam.nl         */
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

static char		*read_sprite_path(char *line)
{
	int		fd;
	char	*path;

	while (*line == ' ' || *line == 'S')
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
	return (path);
}

int				get_sprite(char *line, t_data *data)
{
	if (data->malloced[4] == 'Y')
	{
		return (ft_puterror("get_sprite | multiple elements found."));
	}
	data->sprite_path = read_sprite_path(line);
	if (!data->sprite_path)
	{
		return (ft_puterror("get_sprite | malloc failed."));
	}
	else if (ft_strncmp(data->sprite_path, "file", 100) == 0)
	{
		return (ft_puterror("get_sprite | file could not be opened / found."));
	}
	data->malloced[4] = 'Y';
	return (1);
}
