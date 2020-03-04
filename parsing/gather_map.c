/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 22:01:48 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/04 12:37:18 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

int		replace_map(t_data *data, char *argv)
{
	data->count = 0;
	int x;
	int y;
	int i;

	i = 0;
	x = 0;
	y = 0;
	data->ret = 1;
	data->fd = open(argv, O_RDONLY);
	if (data->fd < 0)
		return (ft_puterror("can not open file."));
	while (data->count < data->map_start)
	{
		data->ret = get_next_line(data->fd, &data->line);
		free(data->line);
		data->count++;
	}
	while (data->ret > 0)
	{
		data->ret = get_next_line(data->fd, &data->line);
		// if (ft_counter(data->line, '0') + ft_counter(data->line, '1') == 0 && data->ret != 0)
		// 	return (ft_puterror("replace_map | invalid map."));
		if (data->ret < 0)
			return (ft_puterror("replace_map | get_next_line failed."));
		while (data->line[i] != '\0')
		{
			// while (data->line[i] == ' ' && data->line[i] != '\0')
			// 	i++;
			if (data->line[i] == 'N' || data->line[i] == 'S' ||
			data->line[i] == 'E' || data->line[i] == 'W')
			{
				if (data->spawn_pos_y > 0 && data->spawn_pos_x > 0)
				{
					free_array(data, y + 2);
					free(data->map);
					free(data->line);
					return (ft_puterror("One or more spawns found."));
				}
				data->spawn_dir = data->line[i];
				data->spawn_pos_x = x;
				data->spawn_pos_y = y;
				data->line[i] = '0';
			}
			if (data->line[i] == '2')
				save_sprite(data, y, x);
			if (data->line[i] == '0' || data->line[i] == '1' || data->line[i] == '2')
				data->map[y][x] = data->line[i] - 48;
			// else
			// 	data->map[y][x] = data->line[i];
			x++;
			i++;
		}
		free(data->line);
		x = 0;
		i = 0;
		y++;
	}
	close(data->fd);
	return (1);
}

int		free_array(t_data *data, int i)
{
	while (i > 0)
	{
		i--;
		free(data->map[i]);
	}
	return (ft_puterror("Malloc has failed."));
}

int			*fill_line(int width)
{
	int *array;
	int i;

	array = malloc(sizeof(int) * width);
	if (!array)
		return (0);
	i = 0;
	while (i < width)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}

void		read_map(char *line, int *width, int *height, int *sprite)
{
	int len;

	len = ft_counter(line, '1') + ft_counter(line, '0');
	*width = (*width < len) ? len : *width;
	*height += 1;
	*sprite += ft_counter(line, '2');
}

int		copy_map(t_data *data, char *argv)
{
	int i;

	i = 0;
	data->map = malloc(sizeof(int*) * data->map_height);
	if (!data->map)
		return (-1);
	while (i < data->map_height)
	{
		data->map[i] = fill_line(data->map_width);
		if (!data->map[i])
		{
			free(data->map);
			return (free_array(data, i));
		}
		i++;
	}
	if (data->sprite_count > 0)
		make_sprite(data);
	if (replace_map(data, argv) != 1)
		return (-1);
	if (data->spawn_pos_y == -1 && data->spawn_pos_x == -1)
	{
		data->malloced[5] = 'Y';
		return (ft_puterror("No Spawning point found."));
	}
	data->malloced[5] = 'Y';
	return (1);
}
