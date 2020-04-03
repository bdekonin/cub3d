/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 19:24:44 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/13 13:22:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void		put_image_to_window(t_vars *vars)
{
	if (vars->image == 0)
	{
		mlx_put_image_to_window(vars->mlx.mlx, \
			vars->mlx.mlx_win, vars->mlx.img, 0, 0);
		vars->image = 1;
	}
	else
	{
		mlx_put_image_to_window(vars->mlx.mlx, \
			vars->mlx.mlx_win, vars->nframe.img, 0, 0);
		vars->image = 0;
	}
}

static void		main_render(t_vars *vars, int x)
{
	while (x < vars->screen.screen_w)
	{
		vars->cam.camera_x = 2 * x / (double)vars->screen.screen_w - 1;
		vars->eng.raydir_x = vars->player.dir_x + vars->cam.planeX * \
														vars->cam.camera_x;
		vars->eng.raydir_y = vars->player.dir_y + vars->cam.planeY * \
														vars->cam.camera_x;
		vars->map.pos_x = (int)vars->player.pos_x;
		vars->map.pos_y = (int)vars->player.pos_y;
		vars->eng.delta_dist_x = fabs(1 / vars->eng.raydir_x);
		vars->eng.delta_dist_y = fabs(1 / vars->eng.raydir_y);
		vars->eng.hit = 0;
		senddir(vars);
		wallsides(vars);
		calculatedraw(vars);
		side(vars);
		step(vars);
		draw_wall(vars, x);
		vars->spr.zbuffer[x] = vars->eng.perp_wall_dist;
		fill_background(x, vars->ren.drawstart, vars->ren.drawend, vars);
		x++;
	}
}

void			renderframe(t_vars *vars)
{
	int i;
	int x;

	i = 0;
	x = 0;
	vars->spr.texwidth = 64;
	vars->spr.texheight = 64;
	main_render(vars, x);
	while (i < vars->spr.sprite_count)
	{
		sprite(vars, i);
		i++;
	}
	sort_sprites(vars);
}

int				frame_loop(t_vars *vars)
{
	renderframe(vars);
	if (vars->key.esc == 1)
		close_win(vars);
	if (vars->key.w == 1)
		forward(vars);
	else if (vars->key.s == 1)
		backwards(vars);
	if (vars->key.l_arr == 1)
		look_left(vars);
	else if (vars->key.r_arr == 1)
		look_right(vars);
	if (vars->key.a == 1)
		walk_left(vars);
	else if (vars->key.d == 1)
		walk_right(vars);
	put_image_to_window(vars);
	return (1);
}
