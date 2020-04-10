/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 13:28:27 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 13:28:28 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static int		spawnpoint(t_data *data, int x, int y, int i)
{
	if (data->line[i] == 'N' || data->line[i] == 'S' ||
	data->line[i] == 'E' || data->line[i] == 'W')
	{
		if (data->spawn_pos_y > 0 && data->spawn_pos_x > 0)
		{
			free(data->line);
			return (ft_puterror("One or more spawns found."));
		}
		data->spawn_dir = data->line[i];
		data->spawn_pos_x = x;
		data->spawn_pos_y = y;
		data->line[i] = '0';
	}
	return (1);
}

/*
** Get next line keeps reading until where the line starts in the .cub file.
*/

static int		read_until_start(t_data *data)
{
	while (data->count < data->map_start)
	{
		data->ret = get_next_line(data->fd, &data->line);
		if (data->ret < 0)
			return (ft_puterror("get next line has failed."));
		free(data->line);
		data->count++;
	}
	return (0);
}

static int		copy_line_2(t_data *data, int x, int y, int i)
{
	if (spawnpoint(data, x, y, i) < 0)
		return (-1);
	if (data->line[i] == '2')
		save_sprite(data, y, x);
	if (data->line[i] == '0' || data->line[i] == '1' || data->line[i] == '2')
		data->map[y][x] = data->line[i] - 48;
	else if (data->line[i] == ' ')
		data->map[y][x] = 9;
	else
	{
		free(data->line);
		return (ft_puterror("Invalid character found in map."));
	}
	return (0);
}

static int		copy_line(t_data *data, int x, int y, int i)
{
	while (data->ret > 0)
	{
		data->ret = get_next_line(data->fd, &data->line);
		if (data->ret < 0)
			return (ft_puterror("replace_map | get_next_line failed."));
		if (ft_counter(data->line, '0') + ft_counter(data->line, '1') == 0 &&
		(y < data->map_height))
			return (ft_puterror("invalid map | empty line found."));
		while (data->line[i] != '\0')
		{
			if (copy_line_2(data, x, y, i) == -1)
				return (-1);
			x++;
			i++;
		}
		free(data->line);
		x = 0;
		i = 0;
		y++;
	}
	return (1);
}

/*
** This is the main function for copying the map over.
*/

int				replace_map(t_data *data, char *argv)
{
	data->count = 0;
	data->ret = 1;
	data->fd = open(argv, O_RDONLY);
	if (data->fd < 0)
		return (ft_puterror("can not open file."));
	if (read_until_start(data) == -1)
		return (-1);
	if (copy_line(data, 0, 0, 0) == -1)
		return (-1);
	close(data->fd);
	return (1);
}
