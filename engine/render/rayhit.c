/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rayhit.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 17:56:11 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 13:23:38 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void		search_hit(t_vars *vars)
{
	while (vars->eng.hit == 0)
	{
		if (vars->eng.side_dist_x < vars->eng.side_dist_y)
		{
			vars->eng.side_dist_x += vars->eng.delta_dist_x;
			vars->map.pos_x += vars->eng.step_x;
			vars->eng.side = 0;
		}
		else
		{
			vars->eng.side_dist_y += vars->eng.delta_dist_y;
			vars->map.pos_y += vars->eng.step_y;
			vars->eng.side = 1;
		}
		if (vars->map.map[vars->map.pos_y][vars->map.pos_x] > 0 \
		&& vars->map.map[vars->map.pos_y][vars->map.pos_x] != 2)
			vars->eng.hit = 1;
	}
}

/*
** Will send out array and will set step on the side which it should be.
** this is later used to set the appropriate wall texture.
*/

void			senddir(t_vars *vars)
{
	if (vars->eng.raydir_x < 0)
	{
		vars->eng.step_x = -1;
		vars->eng.side_dist_x = (vars->player.pos_x - \
							vars->map.pos_x) * vars->eng.delta_dist_x;
	}
	else
	{
		vars->eng.step_x = 1;
		vars->eng.side_dist_x = (vars->map.pos_x + 1.0 - \
						vars->player.pos_x) * vars->eng.delta_dist_x;
	}
	if (vars->eng.raydir_y < 0)
	{
		vars->eng.step_y = -1;
		vars->eng.side_dist_y = (vars->player.pos_y - \
						vars->map.pos_y) * vars->eng.delta_dist_y;
	}
	else
	{
		vars->eng.step_y = 1;
		vars->eng.side_dist_y = (vars->map.pos_y + 1.0 - \
					vars->player.pos_y) * vars->eng.delta_dist_y;
	}
	search_hit(vars);
}
