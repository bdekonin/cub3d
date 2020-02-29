/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:30:54 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/21 14:31:12 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void drawline(int x, double start, double end, int color, t_vars *vars)
{
	while (start < end)
	{
		my_mlx_pixel_put(vars, x, start, color);
		start++;
	}
}