/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 14:05:55 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 12:50:12 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

void	parse_init(t_data *data)
{
	data->screen_x = -1;
	data->screen_y = -1;
	data->res[0] = 'N';
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
	data->error = 1;

	data->map_height = 0;
	data->map_width = 0;
	data->map_start = -1;
	data->count = 0;
	data->spawn_pos_x = -1;
	data->spawn_pos_y = -1;
	data->ret = 1;
	data->malloced[0] = 'N'; // North
	data->malloced[1] = 'N'; // South
	data->malloced[2] = 'N'; // East
	data->malloced[3] = 'N'; // West
	data->malloced[4] = 'N'; // Sprite
	data->malloced[5] = 'N'; // Map
	data->sprite_count = 0;
}
