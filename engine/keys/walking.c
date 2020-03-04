/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:37:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/04 16:43:41 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void		forward(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x + vars->player.dir_x * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0)
		vars->player.pos_x += vars->player.dir_x * vars->cam.move_speed;
	temp = vars->player.pos_y + vars->player.dir_y * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0)
		vars->player.pos_y += vars->player.dir_y * vars->cam.move_speed;
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
}

void		backwards(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x - vars->player.dir_x * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0)
		vars->player.pos_x -= vars->player.dir_x * vars->cam.move_speed;
	temp = vars->player.pos_y - vars->player.dir_y * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0)
		vars->player.pos_y -= vars->player.dir_y * vars->cam.move_speed;
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
}

void	walk_left(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x - vars->cam.planeX * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0)
		vars->player.pos_x -= vars->cam.planeX * vars->cam.move_speed;
	temp = vars->player.pos_y - vars->cam.planeY * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0)
		vars->player.pos_y -= vars->cam.planeY * vars->cam.move_speed;
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
}

void	walk_right(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x + vars->cam.planeX * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0)
		vars->player.pos_x += vars->cam.planeX * vars->cam.move_speed;
	temp = vars->player.pos_y + vars->cam.planeY * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0)
		vars->player.pos_y += vars->cam.planeY * vars->cam.move_speed;
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
}


void		look_left(t_vars *vars)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = vars->player.dir_x;
	vars->player.dir_x = vars->player.dir_x * cos(-vars->cam.rot_speed)
	- vars->player.dir_y * sin(-vars->cam.rot_speed);
	vars->player.dir_y = old_dir_x * sin(-vars->cam.rot_speed)
	+ vars->player.dir_y * cos(-vars->cam.rot_speed);
	old_plane_x = vars->cam.planeX;
	vars->cam.planeX = vars->cam.planeX * cos(-vars->cam.rot_speed)
	- vars->cam.planeY * sin(-vars->cam.rot_speed);
	vars->cam.planeY = old_plane_x * sin(-vars->cam.rot_speed)
	+ vars->cam.planeY * cos(-vars->cam.rot_speed);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
}

void		look_right(t_vars *vars)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = vars->player.dir_x;
	vars->player.dir_x = vars->player.dir_x * cos(vars->cam.rot_speed)
	- vars->player.dir_y * sin(vars->cam.rot_speed);
	vars->player.dir_y = old_dir_x * sin(vars->cam.rot_speed)
	+ vars->player.dir_y * cos(vars->cam.rot_speed);
	old_plane_x = vars->cam.planeX;
	vars->cam.planeX = vars->cam.planeX * cos(vars->cam.rot_speed)
	- vars->cam.planeY * sin(vars->cam.rot_speed);
	vars->cam.planeY = old_plane_x * sin(vars->cam.rot_speed)
	+ vars->cam.planeY * cos(vars->cam.rot_speed);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
}
