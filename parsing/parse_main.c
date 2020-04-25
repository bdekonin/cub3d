/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 14:26:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/21 22:19:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static void		copy_dir(t_vars *vars, t_data *data)
{
	if (data->spawn_dir == 'N')
	{
		vars->player.dir_y = -1;
		vars->cam.planex = 0.66;
		vars->cam.planey = 0;
	}
	else if (data->spawn_dir == 'E')
	{
		vars->player.dir_x = 1;
		vars->player.dir_y = 0;
		vars->cam.planey = 0.66;
	}
	else if (data->spawn_dir == 'S')
	{
		vars->player.dir_y = 1;
		vars->cam.planex = -0.66;
		vars->cam.planey = 0;
	}
	else if (data->spawn_dir == 'W')
	{
		vars->player.dir_x = -1;
		vars->player.dir_y = 0;
		vars->cam.planey = -0.66;
	}
}

static void		copy_data(t_vars *vars, t_data *data)
{
	vars->screen.screen_w = data->screen_x;
	vars->screen.screen_h = data->screen_y;
	vars->player.pos_x = data->spawn_pos_x;
	vars->player.pos_y = data->spawn_pos_y;
	vars->cam.planex = 0;
	vars->player.dir_x = 0;
	copy_dir(vars, data);
	vars->map.map = data->map;
	vars->map.map_w = data->map_width;
	vars->map.map_h = data->map_height;
	vars->cub.floor_color = data->floor[0] * 65536 +
	data->floor[1] * 256 + data->floor[2];
	vars->cub.ceiling_color = data->ceiling[0] * 65536 +
	data->ceiling[1] * 256 + data->ceiling[2];
	vars->cub.north = data->north_path;
	vars->cub.east = data->east_path;
	vars->cub.south = data->south_path;
	vars->cub.west = data->west_path;
	vars->cub.sprite = data->sprite_path;
	vars->spr.sprite = data->sprite;
	vars->spr.sprite_count = data->sprite_count;
}

static int		parse_loop(t_data *data, int i)
{
	while (data->ret > 0 && data->error != -1)
	{
		i = 0;
		data->ret = get_next_line(data->fd, &data->line);
		if (data->ret < 0)
		{
			parse_free(data);
			return (ft_puterror("parse_main | get_next_line failed."));
		}
		while (data->line[i] == ' ' && data->line[i] != '\0')
			i++;
		if (data->line[i] == '\0' && i != 0)
		{
			ft_puterror("Invalid line");
			return (parse_free(data));
		}
		if (data->line[i] != '\0' && line_select(data, i) == -1)
			data->error = -1;
		free(data->line);
		data->count++;
		if (data->error == -1)
			return (parse_free(data));
	}
	return (1);
}

int				parse_main(t_vars *vars, char *argv)
{
	t_data		data;

	data.fd = open(argv, O_RDONLY);
	if (data.fd < 0)
		return (ft_puterror("Argument not found."));
	parse_init(&data);
	if (parse_loop(&data, 0) == -1)
		return (-1);
	if (close(data.fd) < 0)
		return (ft_puterror("Could not close fd."));
	if (parse_error_check(&data, argv) == -1)
		return (-1);
	copy_data(vars, &data);
	return (data.error);
}
