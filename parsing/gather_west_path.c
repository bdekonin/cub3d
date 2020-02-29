/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_west_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/19 14:04:40 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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
