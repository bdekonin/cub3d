/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:26:30 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/21 14:26:51 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	fill_background(int x, int start, int end, t_vars *vars)
{
	int y;

	y = 0;
	while (y <= start)
	{
		my_mlx_pixel_put(vars, x, y, vars->cub.ceiling_color);
		y++;
	}
	y = end;
	while (y < vars->screen.screen_h)
	{
		my_mlx_pixel_put(vars, x, y, vars->cub.floor_color);
		y++;
	}
}
