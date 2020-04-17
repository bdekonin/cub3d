/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 13:41:15 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/16 17:08:11 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parse_data.h"
#include "cub3d.h"

static int	createmlx(t_vars *vars, char *filename)
{
	vars->mlx.mlx = mlx_init();
	if (!vars->mlx.mlx)
		return (ft_puterror("Failed creating mlx pointer."));
	if (vars->save == 0)
		vars->mlx.mlx_win = mlx_new_window(vars->mlx.mlx, \
				vars->screen.screen_w, vars->screen.screen_h, filename);
	if (vars->save == 0 && !vars->mlx.mlx_win)
		return (ft_puterror("Failed creating mlx window."));
	vars->mlx.img = mlx_new_image(vars->mlx.mlx, vars->screen.screen_w, \
												vars->screen.screen_h);
	if (!vars->mlx.img)
		return (ft_puterror("Failed creating mlx image."));
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img, \
		&vars->mlx.bits_pixel, &vars->mlx.line_length, &vars->mlx.endian);
	if (!vars->mlx.addr)
		return (ft_puterror("Failed getting mlx address."));
	vars->nframe.img = mlx_new_image(vars->mlx.mlx, \
					vars->screen.screen_w, vars->screen.screen_h);
	if (!vars->nframe.img)
		return (ft_puterror("Failed creating mlx image."));
	vars->nframe.addr = mlx_get_data_addr(vars->nframe.img, \
	&vars->nframe.bits_pixel, &vars->nframe.line_length, &vars->nframe.endian);
	if (!vars->nframe.addr)
		return (ft_puterror("Failed getting mlx address."));
	return (1);
}

int			create_img(t_vars *vars, char *filename)
{
	char *ptr;

	ptr = ft_strjoin("cub3d | ", filename);
	if (!ptr)
		return (ft_puterror("Malloc failed."));
	if (createmlx(vars, ptr) == -1)
	{
		free(ptr);
		return (-1);
	}
	free(ptr);
	vars->spr.zbuffer = malloc(sizeof(double) * vars->screen.screen_w);
	if (!vars->spr.zbuffer)
		return (ft_puterror("Malloc has failed"));
	if (file_north(vars) == -1)
		return (-1);
	if (file_east(vars) == -1)
		return (-1);
	if (file_south(vars) == -1)
		return (-1);
	if (file_west(vars) == -1)
		return (-1);
	if (file_sprite(vars) == -1)
		return (-1);
	return (1);
}

int			main(int argc, char **argv)
{
	t_vars		vars;

	if (argc < 2)
		return (ft_puterror("Not enough arguments."));
	if (argc > 3)
		return (ft_puterror("Too many arguments."));
	vars.file_ext = ft_strrchr(argv[1], '.');
	if (!vars.file_ext || ft_strncmp(vars.file_ext, ".cub", 10) != 0)
		return (ft_puterror("Argument is not a .cub file."));
	if (argc > 2 && ft_strncmp(argv[2], "--save", 7))
		return (ft_puterror("Second argument is invalid."));
	else if (argc > 2 && ft_strncmp(argv[2], "--save", 7) == 0)
		vars.save = 1;
	vars.ret = parse_main(&vars, argv[1]);
	if (vars.ret == -1)
		exit(1);
	initialize_rendering(&vars);
	if (create_img(&vars, argv[1]) == -1)
		exit(1);
	if (vars.save == 1)
		createbmp(&vars);
	else
		engine(&vars);
	free(vars.spr.zbuffer);
	exit(0);
}

int			initialize_rendering(t_vars *vars)
{
	int x;
	int y;

	init_key(vars);
	vars->cam.rot_speed = 0.05;
	vars->cam.move_speed = 0.09;
	vars->player.pos_x += 0.45;
	vars->player.pos_y += 0.45;
	if (vars->save == 0)
	{
		mlx_get_screen_size(vars->mlx.mlx, &x, &y);
		vars->screen.screen_h = (vars->screen.screen_h > y) ? y : \
													vars->screen.screen_h;
		vars->screen.screen_w = (vars->screen.screen_w > x) ? x : \
												vars->screen.screen_w;
	}
	return (1);
}

int			engine(t_vars *vars)
{
	mlx_loop_hook(vars->mlx.mlx, frame_loop, vars);
	mlx_hook(vars->mlx.mlx_win, 2, (1L << 0), key_press, vars);
	mlx_hook(vars->mlx.mlx_win, 3, (1L << 1), key_release, vars);
	mlx_hook(vars->mlx.mlx_win, 17, 0L, close_win, vars);
	mlx_loop(vars->mlx.mlx);
	return (1);
}
