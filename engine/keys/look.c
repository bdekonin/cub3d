/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   look.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 12:14:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/09 12:15:31 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
