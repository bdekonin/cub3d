/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 14:06:32 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/24 09:45:00 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

int		check_next(t_data *data, int row, int col, int prev)
{
	int tile;

	if (row < 0 || col < 0 || row >= data->map_height)
		return (0);
	tile = data->map[row][col];
	if (tile == 1 || tile == 6 || tile == 8 || tile == 7 || (data->spawn_pos_x == col
	&& data->spawn_pos_y == row))
		return (1);
	if (tile == 0 || tile == 2 || tile == 3)
	{
		if (tile == 0)
			data->map[row][col] = 8;
		else if (tile == 2)
			data->map[row][col] = 7;
		else
			data->map[row][col] = 6;
		if (check_path(data, row, col, prev))
			return (1);
	}
	return (0);
}

int		check_path(t_data *data, int row, int col, int prev)
{
	if (prev != 2 && !check_next(data, row - 1, col, 1))
		return (0);
	if (prev != 1 && !check_next(data, row + 1, col, 2))
		return (0);
	if (prev != 4 && !check_next(data, row, col - 1, 3))
		return (0);
	if (prev != 3 && !check_next(data, row, col + 1, 4))
		return (0);
	if (prev != 8 && !check_next(data, row - 1, col - 1, 9))
		return (0);
	if (prev != 9 && !check_next(data, row + 1, col + 1, 8))
		return (0);
	if (prev != 5 && !check_next(data, row + 1, col - 1, 6))
		return (0);
	if (prev != 6 && !check_next(data, row - 1, col + 1, 5))
		return (0);
	return (1);
}
