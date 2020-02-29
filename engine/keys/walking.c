/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:37:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/24 11:22:49 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void		forward(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x + vars->player.dir_x * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0 ||
	(vars->map.map[(int)vars->player.pos_y][temp] == 3 && vars->key.space == 1))
		vars->player.pos_x += vars->player.dir_x * vars->cam.move_speed;
	temp = vars->player.pos_y + vars->player.dir_y * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0 ||
	vars->map.map[temp][(int)vars->player.pos_x] == 3)
		vars->player.pos_y += vars->player.dir_y * vars->cam.move_speed;
}

void		backwards(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x - vars->player.dir_x * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0 ||
	vars->map.map[(int)vars->player.pos_y][temp] == 3)
		vars->player.pos_x -= vars->player.dir_x * vars->cam.move_speed;
	temp = vars->player.pos_y - vars->player.dir_y * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0 ||
	vars->map.map[temp][(int)vars->player.pos_x] == 3)
		vars->player.pos_y -= vars->player.dir_y * vars->cam.move_speed;
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
}

void	run(t_vars *vars)
{
	if (vars->key.space == 1)
		vars->cam.move_speed += 0.10;
	else if (vars->key.space == 0)
		vars->cam.move_speed -= 0.10;
}