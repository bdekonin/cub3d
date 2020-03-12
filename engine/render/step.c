/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 19:20:42 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 19:21:38 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** how much to increase the texture coordinate per screen pixel
*/
void step(t_vars *vars)
{
    vars->ren.step = 1.0 * vars->spr.texheight / vars->ren.lineheight;
    vars->ren.tex_pos = (vars->ren.drawstart - vars->screen.screen_h / 2 + 
    vars->ren.lineheight / 2) * vars->ren.step;
}