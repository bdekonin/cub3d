/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 13:41:15 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 18:13:26 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parse_data.h"
#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int initialize_rendering(t_vars *vars);
int engine(t_vars *vars);

static int createmlx(t_vars *vars, char *filename)
{
	vars->mlx.mlx = mlx_init();
	if (!vars->mlx.mlx)
		return (ft_puterror("Failed creating mlx pointer."));
	if (vars->save == 0)
		vars->mlx.mlx_win = mlx_new_window(vars->mlx.mlx, vars->screen.screen_w, vars->screen.screen_h, filename);
	if (!vars->mlx.mlx_win)
		return (ft_puterror("Failed creating mlx window."));
    vars->mlx.img = mlx_new_image(vars->mlx.mlx, vars->screen.screen_w, vars->screen.screen_h);
	if (!vars->mlx.img)
		return (ft_puterror("Failed creating mlx image."));
    vars->mlx.addr = mlx_get_data_addr(vars->mlx.img, &vars->mlx.bits_pixel, &vars->mlx.line_length,
                                 &vars->mlx.endian);
	if (!vars->mlx.addr)
		return (ft_puterror("Failed getting mlx address."));
    vars->nframe.img = mlx_new_image(vars->mlx.mlx, vars->screen.screen_w, vars->screen.screen_h);
	if (!vars->nframe.img)
		return (ft_puterror("Failed creating mlx image."));
    vars->nframe.addr = mlx_get_data_addr(vars->nframe.img, &vars->nframe.bits_pixel, &vars->nframe.line_length,
                                 &vars->nframe.endian);
	if (!vars->nframe.addr)
		return (ft_puterror("Failed getting mlx address."));
	return (1);
}

int create_img(t_vars *vars, char *filename)
{
	char *ptr;
	ptr = ft_strjoin("cub3d | ", filename);
	if (!ptr)
		return (ft_puterror("Malloc failed."));
	if (!createmlx(vars, filename))
		return (-1);
	free(ptr);
	vars->spr.zbuffer = malloc(sizeof(double) * vars->screen.screen_w);
	if (!vars->spr.zbuffer)
		return (ft_puterror("Malloc has failed"));
	if (file_north(vars) == -1)
		return (-1);
	if (file_east(vars) == -1)
		return (-1);
	if (file_south(vars) == -1)
		return (-1);
	if (file_west(vars) == -1)
		return (-1);
	if (file_sprite(vars) == -1)
		return (-1);
	return (1);
}

void sortsprite_one(t_vars *vars)
{
	for (int i = 0; i < vars->spr.sprite_count - 1; i++)
	{
		for (int i = 0; i < vars->spr.sprite_count - 1; i++)
		{
			if (vars->spr.sprite[i][2] < vars->spr.sprite[i + 1][2])
			{
				swap(&vars->spr.sprite[i][0], &vars->spr.sprite[i + 1][0]);
				swap(&vars->spr.sprite[i][1], &vars->spr.sprite[i + 1][1]);
				swap(&vars->spr.sprite[i][2], &vars->spr.sprite[i + 1][2]);
			}
		}
	}
}

void calculate_dist_one(t_vars *vars)
{
	int i;
	int y;
	int x;

	i = 0;
	while (i < vars->spr.sprite_count)
	{
		x = vars->player.pos_x - vars->spr.sprite[i][1];
		x *= (x < 0) ? -1 : 1;
		y = vars->player.pos_y - vars->spr.sprite[i][0];
		y *= (y < 0) ? -1 : 1;
		vars->spr.sprite[i][2] = sqrt(y + x);
		i++;
	}
	sortsprite_one(vars);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	int			ret;
	char		*p;

	if (argc < 2)
		return (ft_puterror("Not enough arguments."));
	if (argc > 3)
		return (ft_puterror("Too many arguments."));
	p = ft_strrchr(argv[1], '.');
	if (!p || ft_strncmp(p, ".cub", 10) != 0)
		return (ft_puterror("Argument is not a .cub file."));
	if (argc > 2 && ft_strncmp(argv[2], "--save", 7))
		return (ft_puterror("Second argument is invalid."));
	else if (argc > 2 && ft_strncmp(argv[2], "--save", 7) == 0)
		vars.save = 1;
	ret = parse_main(&vars, argv[1]);
	if (ret == -1)
		exit(1);
	initialize_rendering(&vars);
	if (create_img(&vars, argv[1]) == -1)
		exit(1);
	if (vars.save == 1)
		createbmp(&vars);
	else
		engine(&vars);
	exit(0);
}

void renderframe(t_vars *vars)
{
	vars->spr.texwidth = 64;
	vars->spr.texheight = 64;
	size_t i;

	i = 0;

	for(int x = 0; x < vars->screen.screen_w; x++)
	{
		vars->cam.camera_x = 2 * x / (double)vars->screen.screen_w - 1;
		vars->eng.raydir_x = vars->player.dir_x + vars->cam.planeX * vars->cam.camera_x;
		vars->eng.raydir_y = vars->player.dir_y + vars->cam.planeY * vars->cam.camera_x;
		vars->map.pos_x = (int)vars->player.pos_x;
		vars->map.pos_y = (int)vars->player.pos_y;

		vars->eng.delta_dist_x = fabs(1 / vars->eng.raydir_x);
		vars->eng.delta_dist_y = fabs(1 / vars->eng.raydir_y);

		vars->eng.hit = 0;
		senddir(vars);
		wallsides(vars);
		calculatedraw(vars);

		//texturing calculations
		int texNum = vars->map.map[vars->map.pos_y][vars->map.pos_x]; //1 subtracted from it so that texture 0 can be used!
			double wallX;
			if (vars->eng.side == 0)
				wallX = vars->player.pos_y + vars->eng.perp_wall_dist * vars->eng.raydir_y;
			else
				wallX = vars->player.pos_x + vars->eng.perp_wall_dist * vars->eng.raydir_x;
			wallX -= floor((wallX));

		vars->ren.tex_x = (int)(wallX * (double)(vars->spr.texwidth));
		if (vars->eng.side == 0 && vars->eng.raydir_x > 0)
			vars->ren.tex_x = vars->spr.texwidth - vars->ren.tex_x - 1;
		if (vars->eng.side == 1 && vars->eng.raydir_y < 0)
			vars->ren.tex_x = vars->spr.texwidth - vars->ren.tex_x - 1;


		// How much to increase the texture coordinate per screen pixel
    	double step = 1.0 * vars->spr.texheight / vars->ren.lineheight;
		double texPos = (vars->ren.drawstart - vars->screen.screen_h / 2 + vars->ren.lineheight / 2) * step;

		if (vars->map.map[(int)vars->player.pos_y][(int)vars->player.pos_x] == 3)
			vars->map.map[(int)vars->player.pos_y][(int)vars->player.pos_x] = 0;
			
		for(int y = vars->ren.drawstart; y<vars->ren.drawend; y++)
		{
			if (texNum != 2)
			{
				vars->ren.tex_y = (int)texPos & (vars->spr.texheight - 1);
				texPos += step;
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
		}
		vars->spr.zbuffer[x] = vars->eng.perp_wall_dist;
		fill_background(x, vars->ren.drawstart, vars->ren.drawend, vars);
	}
	while (i < vars->spr.sprite_count)
	{
		sprite(vars, i);
		i++;
	}
	calculate_dist_one(vars);
}

int testing(t_vars *vars)
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
	if (vars->image == 0)
	{
		mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
		vars->image = 1;
	}
	else
	{
		mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->nframe.img, 0, 0);
		vars->image = 0;
	}
	return (1);
}

int initialize_rendering(t_vars *vars)
{
	int x;
	int y;
	init_key(vars);
	vars->cam.rot_speed = 0.05;
	vars->cam.move_speed = 0.09;
	vars->player.pos_x += 0.5;
	vars->player.pos_y += 0.5;
	if (vars->save == 0)
	{
		mlx_get_screen_size(vars->mlx.mlx, &x, &y);
		vars->screen.screen_h = (vars->screen.screen_h > y) ? y : vars->screen.screen_h;
		vars->screen.screen_w = (vars->screen.screen_w > x) ? x : vars->screen.screen_w;
	}
	return (1);
}

int engine(t_vars *vars)
{
	mlx_loop_hook(vars->mlx.mlx, testing, vars);
	mlx_hook(vars->mlx.mlx_win, 2, (1L << 0), key_press, vars);
	mlx_hook(vars->mlx.mlx_win, 3, (1L << 1), key_release, vars);
	mlx_hook(vars->mlx.mlx_win, 17, 0L, close_win, vars);
	mlx_loop(vars->mlx.mlx);
	return (1);
}
