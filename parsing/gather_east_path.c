/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_east_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/19 14:04:00 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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
