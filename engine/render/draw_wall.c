/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_wall.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 18:23:44 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/06 21:21:36 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	get_i(t_vars *vars)
{
	if (vars->tex.w_tex == 'N')
		return (0);
	else if (vars->tex.w_tex == 'E')
		return (1);
	else if (vars->tex.w_tex == 'S')
		return (2);
	else
		return (3);
}

/*
** This will draw the right texture on the image
*/

void		draw_wall(t_vars *vars, int x)
{
	int tex_num;
	int y;
	int i;

	i = get_i(vars);
	y = vars->ren.drawstart;
	tex_num = vars->map.map[vars->map.pos_y][vars->map.pos_x];
	while (y < vars->ren.drawend)
	{
		if (tex_num != 2)
		{
			vars->ren.tex_y = (int)vars->ren.tex_pos & \
								(vars->spr.texheight - 1);
			vars->ren.tex_pos += vars->ren.step;
			vars->color = *(unsigned int*)(vars->tex.addr[i] + \
				(vars->ren.tex_y * vars->tex.line_length[i] + \
				vars->ren.tex_x * (vars->tex.bits_pixel[i] / 8)));
			my_mlx_pixel_put(vars, x, y, vars->color);
		}
		y++;
	}
}
