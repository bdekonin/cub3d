/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 19:20:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/06 21:21:50 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** This will use the made variables to calculate how much longer a line has,
** to be.
*/

void	step(t_vars *vars)
{
	vars->ren.step = 1.0 * vars->spr.texheight / vars->ren.lineheight;
	vars->ren.tex_pos = (vars->ren.drawstart - vars->screen.screen_h / 2 + \
	vars->ren.lineheight / 2) * vars->ren.step;
}
