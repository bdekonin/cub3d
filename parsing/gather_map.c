/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 22:01:48 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 15:09:42 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

int			free_map(t_data *data, int i)
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
		array[i] = 9;
		i++;
	}
	return (array);
}

void		read_map(char *line, int *width, int *height, int *sprite)
{
	int len;

	len = ft_counter(line, '1') + ft_counter(line, '0') + ft_counter(line, ' ');
	*width = (*width < len) ? len : *width;
	*height += 1;
	*sprite += ft_counter(line, '2');
}

int			copy_map(t_data *data, char *argv)
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
			return (free_map(data, i));
		}
		i++;
	}
	data->malloced[5] = 'Y';
	if (data->sprite_count > 0 && make_sprite(data) == -1)
		return (-1);
	if (replace_map(data, argv) != 1)
		return (-1);
	if (data->spawn_pos_y == -1 && data->spawn_pos_x == -1)
		return (ft_puterror("No Spawning point found."));
	return (1);
}
