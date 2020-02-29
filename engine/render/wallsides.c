/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wallsides.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 11:10:50 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/24 12:34:37 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void wallsides(t_vars *vars)
{
	if (vars->eng.side == 0)
	{
		if (vars->eng.step_x > 0 && vars->map.pos_x >
		(int)vars->player.pos_x && vars->eng.side == 0)
			vars->tex.w_tex = 'W';
		if (vars->eng.step_x < 0 && vars->map.pos_x <
		(int)vars->player.pos_x && vars->eng.side == 0)
			vars->tex.w_tex = 'E';
	}
	if (vars->eng.side == 1)
	{
		if (vars->eng.step_y > 0 && vars->map.pos_y >
		(int)vars->player.pos_y && vars->eng.side == 1)
			vars->tex.w_tex = 'S';
		if (vars->eng.step_y < 0 && vars->map.pos_y <
		(int)vars->player.pos_y && vars->eng.side - 0)
			vars->tex.w_tex = 'N';
	}
	if (vars->eng.side == 0)
		vars->eng.perp_wall_dist = (vars->map.pos_x - vars->player.pos_x +
		(1 - vars->eng.step_x) / 2) / vars->eng.raydir_x;
	else
		vars->eng.perp_wall_dist = (vars->map.pos_y - vars->player.pos_y +
		(1 - vars->eng.step_y) / 2) / vars->eng.raydir_y;
}
