/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_sprite.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 14:14:22 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/02 16:27:57 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static double			*fill_line_sprite(int width)
{
	double *array;
	int i;

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

int make_sprite(t_data *data)
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
			free(data->map);
			return (free_sprites(data, i));
		}
		i++;
	}
	return (1);
}

void save_sprite(t_data *data, int y, int x)
{
	static int i;

	data->sprite[i][0] = y;
	data->sprite[i][1] = x;
	data->sprite[i][0] += 0.5;
	data->sprite[i][1] += 0.5;
	i++;
}

void swap(double *xp, double *yp)  
{  
	double temp;
	
	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void sortsprite_init(t_data *data)
{
	for (int i = 0; i < data->sprite_count - 1; i++)
	{
		for (int i = 0; i < data->sprite_count - 1; i++)
		{
			if (data->sprite[i][2] < data->sprite[i + 1][2])
			{
				swap(&data->sprite[i][0], &data->sprite[i + 1][0]);
				swap(&data->sprite[i][1], &data->sprite[i + 1][1]);
				swap(&data->sprite[i][2], &data->sprite[i + 1][2]);
			}
		}
	}
}

void calculate_dist(t_data *data)
{
	int i;
	int y;
	int x;

	i = 0;
	while (i < data->sprite_count)
	{
		x = data->spawn_pos_x - data->sprite[i][1];
		x *= (x < 0) ? -1 : 1;
		y = data->spawn_pos_y - data->sprite[i][0];
		y *= (y < 0) ? -1 : 1;
		data->sprite[i][2] = sqrt(y + x);
		i++;
	}
	sortsprite_init(data);
}

int		free_sprites(t_data *data, int i)
{
	while (i > 0)
	{
		i--;
		free(data->sprite[i]);
	}
	return (ft_puterror("Malloc has failed for sprites."));
}
