/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_wall.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 18:23:44 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 18:38:24 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** This will draw the right texture on the image
*/
void draw_wall(t_vars *vars, int x)
{
	int tex_num;
	int y;
	
	y = vars->ren.drawstart;
	tex_num = vars->map.map[vars->map.pos_y][vars->map.pos_x];
	while(y < vars->ren.drawend)
	{
		if (tex_num != 2)
		{
			vars->ren.tex_y = (int)vars->ren.tex_pos & (vars->spr.texheight - 1);
			vars->ren.tex_pos += vars->ren.step;
			if (vars->tex.w_tex == 'N')
				vars->color = *(unsigned int*)(vars->tex.addr[0] + (vars->ren.tex_y * vars->tex.line_length[0] + vars->ren.tex_x * (vars->tex.bits_pixel[0] / 8)));
			else if (vars->tex.w_tex == 'E')
				vars->color = *(unsigned int*)(vars->tex.addr[1] + (vars->ren.tex_y * vars->tex.line_length[1] + vars->ren.tex_x * (vars->tex.bits_pixel[1] / 8)));
			else if (vars->tex.w_tex == 'S')
				vars->color = *(unsigned int*)(vars->tex.addr[2] + (vars->ren.tex_y * vars->tex.line_length[2] + vars->ren.tex_x * (vars->tex.bits_pixel[2] / 8)));
			else if (vars->tex.w_tex == 'W')
				vars->color = *(unsigned int*)(vars->tex.addr[3] + (vars->ren.tex_y * vars->tex.line_length[3] + vars->ren.tex_x * (vars->tex.bits_pixel[3] / 8)));
			my_mlx_pixel_put(vars, x, y, vars->color);
		}
		y++;
	}
}