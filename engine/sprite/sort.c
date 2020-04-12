/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 19:31:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/12 14:19:17 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void		swap_sprites(t_vars *vars)
{
	int i;
	int j;

	j = 0;
	while (j < vars->spr.sprite_count - 1)
	{
		i = 0;
		while (i < vars->spr.sprite_count - 1)
		{
			if (vars->spr.sprite[i][2] < vars->spr.sprite[i + 1][2])
			{
				ft_swap(&vars->spr.sprite[i][0], &vars->spr.sprite[i + 1][0]);
				ft_swap(&vars->spr.sprite[i][1], &vars->spr.sprite[i + 1][1]);
				ft_swap(&vars->spr.sprite[i][2], &vars->spr.sprite[i + 1][2]);
			}
			i++;
		}
		j++;
	}
}

void		sort_sprites(t_vars *vars)
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
	swap_sprites(vars);
}
