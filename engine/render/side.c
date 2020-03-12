/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   side.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 19:12:09 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 19:20:13 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void side(t_vars *vars)
{
    if (vars->eng.side == 0)
        vars->ren.wall_x = vars->player.pos_y + vars->eng.perp_wall_dist * 
                                                        vars->eng.raydir_y;
    else
        vars->ren.wall_x = vars->player.pos_x + vars->eng.perp_wall_dist * 
                                                        vars->eng.raydir_x;
    vars->ren.wall_x -= floor((vars->ren.wall_x));

    vars->ren.tex_x = (int)(vars->ren.wall_x * (double)(vars->spr.texwidth));
    if (vars->eng.side == 0 && vars->eng.raydir_x > 0)
        vars->ren.tex_x = vars->spr.texwidth - vars->ren.tex_x - 1;
    if (vars->eng.side == 1 && vars->eng.raydir_y < 0)
        vars->ren.tex_x = vars->spr.texwidth - vars->ren.tex_x - 1;
}