/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_north_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:00:20 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/02 16:27:13 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static char		*read_north_path(char *line)
{
	int		fd;
	char	*path;

	while (*line == ' ' || *line == 'N' || *line == 'O')
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
	close (fd);
	return (path);
}

int				get_north(char *line, t_data *data)
{
	if (data->malloced[0] == 'Y')
	{
		return (ft_puterror("get_north | multiple elements found."));
	}
	data->north_path = read_north_path(line);
	if (!data->north_path)
	{
		return (ft_puterror("get_north | malloc failed."));
	}
	else if (ft_strncmp(data->north_path, "file", 100) == 0)
	{
		return (ft_puterror("get_north | file could not be opened / found."));
	}
	data->malloced[0] = 'Y';
	return (1);
}
