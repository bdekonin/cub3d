/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_pixel_put.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:28:53 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/21 14:29:46 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->mlx.addr + (y * vars->mlx.line_length + x *
	(vars->mlx.bits_pixel / 8));
	*(unsigned int*)dst = color;
}