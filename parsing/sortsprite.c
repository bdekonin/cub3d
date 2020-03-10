/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sortsprite.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 21:06:39 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/09 21:07:04 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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