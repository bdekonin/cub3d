/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 13:41:15 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/02 16:31:26 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parse_data.h"
#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int init_engine(t_vars *vars);
int engine_init(t_vars *vars);

void map(t_vars *vars)
{
	for (int y = 0; y < vars->map.map_h; y++)
	{
		for(int loop = 0; loop < vars->map.map_w; loop++)
		{
			if ((int)vars->player.pos_y == y && (int)vars->player.pos_x == loop)
			{
				printf("\033[0;31m");
				printf("N");
				printf("\033[0m");
			}
			else if (vars->map.map[y][loop] == 1)
			{
				printf("\033[01;33m");
				printf("%d", vars->map.map[y][loop]);
				printf("\033[0m");
			}
			else if (vars->map.map[y][loop] == 2)
			{
				printf("\033[0;34m");
				printf("%d", vars->map.map[y][loop]);
				printf("\033[0m");
			}
			else
				printf("%d", vars->map.map[y][loop]);
		}
		printf("\n");
	}
	printf("\n");

}

int file_north(t_vars *vars);
int file_east(t_vars *vars);
int file_south(t_vars *vars);
int file_west(t_vars *vars);
int file_sprite(t_vars *vars);

int create_img(t_vars *vars)
{
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

int	main(int argc, char **argv)
{
	t_vars		vars;
	int			ret;
	char		*p;
	if (argc < 2)
		return (ft_puterror("Not enough arguments."));
	p = ft_strrchr(argv[1], '.');
	if (ft_strncmp(p, ".cub", 10) != 0)
		return (ft_puterror("Argument is not a .cub file."));
	printf("%s\n\n", argv[1]);
	ret = parse_main(&vars, argv[1]);
	if (ret == -1)
		return (-1);
	else if (argc < 2 || ret == 0)
		return (ft_puterror("Argument not found."));
	init_engine(&vars);
	if (create_img(&vars) == -1)
		return (-1);
	engine_init(&vars);
	return (1);
}

void test(t_vars *vars)
{
	int texWidth = 64;
	int	texHeight = 64;
	double ZBuffer[vars->screen.screen_w];
	
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

		if (vars->eng.raydir_x < 0)
		{
			vars->eng.step_x = -1;
			vars->eng.side_dist_x = (vars->player.pos_x - vars->map.pos_x) * vars->eng.delta_dist_x;
		}
		else
		{
			vars->eng.step_x = 1;
			vars->eng.side_dist_x = (vars->map.pos_x + 1.0 - vars->player.pos_x) * vars->eng.delta_dist_x;
		}
		if (vars->eng.raydir_y < 0)
		{
			vars->eng.step_y = -1;
			vars->eng.side_dist_y = (vars->player.pos_y - vars->map.pos_y) * vars->eng.delta_dist_y;
		}
		else
		{
			vars->eng.step_y = 1;
			vars->eng.side_dist_y = (vars->map.pos_y + 1.0 - vars->player.pos_y) * vars->eng.delta_dist_y;
		}
		//perfom DDA
		while (vars->eng.hit == 0)
		{
			//jump to next map square
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
			//check if array vars->eng.hit wall
			if (vars->map.map[vars->map.pos_y][vars->map.pos_x] > 0 && vars->map.map[vars->map.pos_y][vars->map.pos_x] != 2)
				vars->eng.hit = 1;
		}
		
		wallsides(vars);

		// calcuate line height
		int lineHeight = (int)vars->screen.screen_h / vars->eng.perp_wall_dist;

		//calculate lowest heighest pixel
		int drawStart = -lineHeight / 2 + vars->screen.screen_h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + vars->screen.screen_h / 2; 
		if (drawEnd >= vars->screen.screen_h)
			drawEnd = vars->screen.screen_h - 1;

		//texturing calculations
		int texNum = vars->map.map[vars->map.pos_y][vars->map.pos_x]; //1 subtracted from it so that texture 0 can be used!
			double wallX;
			if (vars->eng.side == 0)
				wallX = vars->player.pos_y + vars->eng.perp_wall_dist * vars->eng.raydir_y;
			else
				wallX = vars->player.pos_x + vars->eng.perp_wall_dist * vars->eng.raydir_x;
			wallX -= floor((wallX));

		int texX = (int)(wallX * (double)(texWidth));
		if (vars->eng.side == 0 && vars->eng.raydir_x > 0)
			texX = texWidth - texX - 1;
		if (vars->eng.side == 1 && vars->eng.raydir_y < 0)
			texX = texWidth - texX - 1;


		// How much to increase the texture coordinate per screen pixel
    	double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - vars->screen.screen_h / 2 + lineHeight / 2) * step;

		if (vars->map.map[(int)vars->player.pos_y][(int)vars->player.pos_x] == 3)
			vars->map.map[(int)vars->player.pos_y][(int)vars->player.pos_x] = 0;
			
		for(int y = drawStart; y<drawEnd; y++)
		{
			if (texNum != 2)
			{
			unsigned int color;
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (vars->tex.w_tex == 'N')
				color = *(unsigned int*)(vars->tex.addr[0] + (texY * vars->tex.line_length[0] + texX * (vars->tex.bits_pixel[0] / 8)));
			else if (vars->tex.w_tex == 'E')
				color = *(unsigned int*)(vars->tex.addr[1] + (texY * vars->tex.line_length[1] + texX * (vars->tex.bits_pixel[1] / 8)));
			else if (vars->tex.w_tex == 'S')
				color = *(unsigned int*)(vars->tex.addr[2] + (texY * vars->tex.line_length[2] + texX * (vars->tex.bits_pixel[2] / 8)));
			else if (vars->tex.w_tex == 'W')
				color = *(unsigned int*)(vars->tex.addr[3] + (texY * vars->tex.line_length[3] + texX * (vars->tex.bits_pixel[3] / 8)));
			my_mlx_pixel_put(vars, x, y, color);
			}
		ZBuffer[x] = vars->eng.perp_wall_dist;
		}
		fill_background(x, drawStart, drawEnd, vars);
	}
	for(int i = 0; i < vars->spr.sprite_count; i++)
	{
		double spriteY = vars->spr.sprite[i][0] - vars->player.pos_y;
		double spriteX = vars->spr.sprite[i][1] - vars->player.pos_x;

		double invDet = 1.0 / (vars->cam.planeX * vars->player.dir_y - vars->player.dir_x * vars->cam.planeY);
		double transformX = invDet * (vars->player.dir_y * spriteX - vars->player.dir_x * spriteY);
		double transformY = invDet * (-vars->cam.planeY * spriteX + vars->cam.planeX * spriteY);

		int spriteScreenX = (int)(vars->screen.screen_w / 2) * (1 + transformX / transformY);
		
		int spriteHeight = fabs((int)vars->screen.screen_h / transformY);

		int drawStartY = -spriteHeight / 2 + vars->screen.screen_h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + vars->screen.screen_h / 2;
		if (drawEndY >= vars->screen.screen_h)
			drawEndY = vars->screen.screen_h - 1;

		int spriteWidth = fabs((int)vars->screen.screen_h / transformY);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= vars->screen.screen_w)
			drawEndX = vars->screen.screen_w - 1;
		
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			unsigned int color;
			int texX = (256 *(stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < vars->screen.screen_w && transformY < ZBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++)
			{
				int d = y * 256 - vars->screen.screen_h * 128 + spriteHeight * 128;
				int texY = (d * texHeight) / spriteHeight / 256;
				color = *(unsigned int*)(vars->tex.addr[4] + (texY * vars->tex.line_length[4] + texX * (vars->tex.bits_pixel[4] / 8)));
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(vars, stripe, y, color);
			}
		}
	}	
}

int testing(t_vars *vars)
{
	test(vars);
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
		// run(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
	return (1);
}

int init_engine(t_vars *vars)
{
	vars->mlx.mlx = mlx_init();
    vars->mlx.mlx_win = mlx_new_window(vars->mlx.mlx, vars->screen.screen_w, vars->screen.screen_h, "Cub3d!");
    vars->mlx.img = mlx_new_image(vars->mlx.mlx, vars->screen.screen_w, vars->screen.screen_h);
    vars->mlx.addr = mlx_get_data_addr(vars->mlx.img, &vars->mlx.bits_pixel, &vars->mlx.line_length,
                                 &vars->mlx.endian);
	init_key(vars);
	vars->cam.planeX = 0;
	vars->cam.planeY = 0.66;
	vars->cam.rot_speed = 0.08;
	vars->cam.move_speed = 0.10;
	create_img(vars);
	return (1);
}

int engine_init(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
	mlx_loop_hook(vars->mlx.mlx, testing, vars);
	mlx_hook(vars->mlx.mlx_win, 2, (1L << 0), key_press, vars);
	mlx_hook(vars->mlx.mlx_win, 3, (1L << 1), key_release, vars);
	mlx_hook(vars->mlx.mlx_win, 17, 0L, close_win, vars);
	mlx_loop(vars->mlx.mlx);
	return (1);
}
