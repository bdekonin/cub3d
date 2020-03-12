/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 19:31:14 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 19:32:34 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


static void sortsprite_one(t_vars *vars)
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

void sort_sprites(t_vars *vars)
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