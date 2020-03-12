/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 15:24:30 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 11:46:19 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void		drawspritey(t_vars *vars, int stripe)
{
	int y;
	int d;

	y = vars->spr.drawstart_y;
	while (y < vars->spr.drawend_y)
	{
		d = y * 256 - vars->screen.screen_h * 128 + \
		vars->spr.spriteheight * 128;
		vars->ren.tex_y = (d * vars->tex.h[4]) / vars->spr.spriteheight / 256;
		vars->color = *(unsigned int*)(vars->tex.addr[4] + (vars->ren.tex_y * \
		vars->tex.line_length[4] + vars->ren.tex_x * \
		(vars->tex.bits_pixel[4] / 8)));
		if ((vars->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(vars, stripe, y, vars->color);
		y++;
	}
}

static void		drawspritex(t_vars *vars)
{
	int stripe;

	stripe = vars->spr.drawstart_x;
	while (stripe < vars->spr.drawend_x)
	{
		vars->ren.tex_x = (256 * (stripe - (-vars->spr.spritewidth / 2 + \
		vars->spr.spritescreenx)) * vars->tex.w[4] / vars->spr.spritewidth) \
		/ 256;
		if (vars->spr.transform_y > 0 && stripe > 0 && stripe < \
		vars->screen.screen_w && vars->spr.transform_y < \
		vars->spr.zbuffer[stripe])
			drawspritey(vars, stripe);
		stripe++;
	}
}

static void		calculate_sprites(t_vars *vars, size_t i)
{
	vars->spr.sprite_y = vars->spr.sprite[i][0] - vars->player.pos_y;
	vars->spr.sprite_x = vars->spr.sprite[i][1] - vars->player.pos_x;
	vars->spr.invdet = 1.0 / (vars->cam.planeX * vars->player.dir_y - \
								vars->player.dir_x * vars->cam.planeY);
	vars->spr.transform_x = vars->spr.invdet * (vars->player.dir_y * \
		vars->spr.sprite_x - vars->player.dir_x * vars->spr.sprite_y);
	vars->spr.transform_y = vars->spr.invdet * (-vars->cam.planeY * \
		vars->spr.sprite_x + vars->cam.planeX * vars->spr.sprite_y);
	vars->spr.spritescreenx = (int)(vars->screen.screen_w / 2) * (1 + \
		vars->spr.transform_x / vars->spr.transform_y);
	vars->spr.spriteheight = fabs((int)vars->screen.screen_h / \
		vars->spr.transform_y);
	vars->spr.drawstart_y = -vars->spr.spriteheight / 2 + \
		vars->screen.screen_h / 2;
}

void			sprite(t_vars *vars, size_t i)
{
	calculate_sprites(vars, i);
	if (vars->spr.drawstart_y < 0)
		vars->spr.drawstart_y = 0;
	vars->spr.drawend_y = vars->spr.spriteheight / 2 + \
								vars->screen.screen_h / 2;
	if (vars->spr.drawend_y >= vars->screen.screen_h)
		vars->spr.drawend_y = vars->screen.screen_h - 1;
	vars->spr.spritewidth = fabs((int)vars->screen.screen_h \
									/ vars->spr.transform_y);
	vars->spr.drawstart_x = -vars->spr.spritewidth / 2 + \
										vars->spr.spritescreenx;
	if (vars->spr.drawstart_x < 0)
		vars->spr.drawstart_x = 0;
	vars->spr.drawend_x = vars->spr.spritewidth / 2 + \
										vars->spr.spritescreenx;
	if (vars->spr.drawend_x >= vars->screen.screen_w)
		vars->spr.drawend_x = vars->screen.screen_w - 1;
	drawspritex(vars);
}
