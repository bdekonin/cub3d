/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_sprite.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 14:14:22 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 13:00:03 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static double	*fill_line_sprite(int width)
{
	double	*array;
	int		i;

	array = malloc(sizeof(double) * width);
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

int				make_sprite(t_data *data)
{
	int i;

	i = 0;
	data->sprite = malloc(sizeof(double*) * data->sprite_count);
	if (!data->sprite)
		return (-1);
	while (i < data->sprite_count)
	{
		data->sprite[i] = fill_line_sprite(3);
		if (!data->sprite[i])
		{
			free_sprites(data, i + 1);
			free(data->sprite);
			return (-1);
		}
		i++;
	}
	return (1);
}

void			save_sprite(t_data *data, int y, int x)
{
	static int i;

	data->sprite[i][0] = y;
	data->sprite[i][1] = x;
	data->sprite[i][0] += 0.5;
	data->sprite[i][1] += 0.5;
	i++;
}

int				free_sprites(t_data *data, int i)
{
	while (i > 0)
	{
		i--;
		free(data->sprite[i]);
	}
	return (-1);
}
