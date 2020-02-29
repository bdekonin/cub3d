/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_south_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/18 18:35:36 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static char		*read_south_path(char *line)
{
	int		fd;
	char	*path;

	while (*line == ' ' || *line == 'S' || *line == 'O')
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
	return (path);
}

int				get_south(char *line, t_data *data)
{
	if (data->malloced[1] == 'Y')
	{
		return (ft_puterror("get_south | multiple elements found."));
	}
	data->south_path = read_south_path(line);
	if (!data->south_path)
	{
		return (ft_puterror("get_south| malloc failed."));
	}
	else if (ft_strncmp(data->south_path, "file", 100) == 0)
	{
		return (ft_puterror("get_south | file could not be opened / found."));
	}
	data->malloced[1] = 'Y';
	return (1);
}
