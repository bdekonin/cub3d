/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculatedraw.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 18:01:37 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/06 21:21:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** this function will calculate the height of the line to be drawn.
** It will use the var perp_wall_dist to measure the lineheight.
** perp_wall_dist is the distance from the player pos to the hit wall.
** If the drawstart (e.g distance is to big or to small it can go below zero)
** therefor if it reaches that we make is zero
*/

void	calculatedraw(t_vars *vars)
{
	vars->ren.lineheight = (int)vars->screen.screen_h /\
	vars->eng.perp_wall_dist;
	vars->ren.drawstart = -vars->ren.lineheight / 2 + vars->screen.screen_h / 2;
	if (vars->ren.drawstart < 0)
		vars->ren.drawstart = 0;
	vars->ren.drawend = vars->ren.lineheight / 2 + vars->screen.screen_h / 2;
	if (vars->ren.drawend >= vars->screen.screen_h)
		vars->ren.drawend = vars->screen.screen_h - 1;
}
