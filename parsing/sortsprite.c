/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sortsprite.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 21:06:39 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/26 08:01:17 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"
#include <math.h>

static void		swap_sprites_data(t_data *data)
{
	int i;
	int j;

	j = 0;
	while (j < data->sprite_count - 1)
	{
		i = 0;
		while (i < data->sprite_count - 1)
		{
			if (data->sprite[i][2] < data->sprite[i + 1][2])
			{
				ft_swap(&data->sprite[i][0], &data->sprite[i + 1][0]);
				ft_swap(&data->sprite[i][1], &data->sprite[i + 1][1]);
				ft_swap(&data->sprite[i][2], &data->sprite[i + 1][2]);
			}
			i++;
		}
		j++;
	}
}

void			calculate_dist(t_data *data)
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
	swap_sprites_data(data);
}
