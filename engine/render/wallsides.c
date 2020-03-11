/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wallsides.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 11:10:50 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 18:20:44 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Based on the wallsided function. we will now set the appropriate height and
** width's for the texture. so a higher quality texture will not have the same
** resolution as a 8bit picture.
*/
static void set_texturesize(t_vars *vars)
{
	if (vars->tex.w_tex == 'N')
	{
		vars->spr.texwidth = vars->tex.w[0];
		vars->spr.texheight = vars->tex.h[0];
	}
	else if (vars->tex.w_tex == 'E')
	{
		vars->spr.texwidth = vars->tex.w[1];
		vars->spr.texheight = vars->tex.h[1];
	}
	else if (vars->tex.w_tex == 'S')
	{
		vars->spr.texwidth = vars->tex.w[2];
		vars->spr.texheight = vars->tex.h[2];
	}
	else if (vars->tex.w_tex == 'W')
	{
		vars->spr.texwidth = vars->tex.w[3];
		vars->spr.texheight = vars->tex.h[3];
	}
}


/*
** This will calculate which texture has to be printed.
** it will use mostly the step_x or step_y var to see which side should be which.
** if the raydir_x < 0 step_x is -1; So its to the left and this will give us the East texture;
*/
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
