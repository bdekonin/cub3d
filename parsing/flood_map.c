/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 14:06:32 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 12:49:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

int		check_next(t_data *data, int y, int x, int prev)
{
	int tile;

	if (y < 0 || x < 0 || y >= data->map_height)
		return (0);
	tile = data->map[y][x];
	if (tile == 1 || tile == 6 || tile == 8 || tile == 7 || \
	(data->spawn_pos_x == x
	&& data->spawn_pos_y == y))
		return (1);
	if (tile == 0 || tile == 2 || tile == 3)
	{
		if (tile == 0)
			data->map[y][x] = 8;
		else if (tile == 2)
			data->map[y][x] = 7;
		else
			data->map[y][x] = 6;
		if (check_path(data, y, x, prev))
			return (1);
	}
	return (0);
}

int		check_path(t_data *data, int y, int x, int prev)
{
	if (prev != 2 && !check_next(data, y - 1, x, 1))
		return (0);
	if (prev != 1 && !check_next(data, y + 1, x, 2))
		return (0);
	if (prev != 4 && !check_next(data, y, x - 1, 3))
		return (0);
	if (prev != 3 && !check_next(data, y, x + 1, 4))
		return (0);
	if (prev != 8 && !check_next(data, y - 1, x - 1, 9))
		return (0);
	if (prev != 9 && !check_next(data, y + 1, x + 1, 8))
		return (0);
	if (prev != 5 && !check_next(data, y + 1, x - 1, 6))
		return (0);
	if (prev != 6 && !check_next(data, y - 1, x + 1, 5))
		return (0);
	return (1);
}
