/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:37:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/09 12:15:57 by bdekonin      ########   odam.nl         */
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
}

void		walk_left(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x - vars->cam.planeX * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0)
		vars->player.pos_x -= vars->cam.planeX * vars->cam.move_speed;
	temp = vars->player.pos_y - vars->cam.planeY * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0)
		vars->player.pos_y -= vars->cam.planeY * vars->cam.move_speed;
}

void		walk_right(t_vars *vars)
{
	int temp;

	temp = vars->player.pos_x + vars->cam.planeX * vars->cam.move_speed;
	if (vars->map.map[(int)vars->player.pos_y][temp] == 0)
		vars->player.pos_x += vars->cam.planeX * vars->cam.move_speed;
	temp = vars->player.pos_y + vars->cam.planeY * vars->cam.move_speed;
	if (vars->map.map[temp][(int)vars->player.pos_x] == 0)
		vars->player.pos_y += vars->cam.planeY * vars->cam.move_speed;
}
