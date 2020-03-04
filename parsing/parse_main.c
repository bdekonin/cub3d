/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 14:26:42 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/04 16:07:50 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"
#include "../cub3d.h"

static void copy_dir(t_vars *vars, t_data *data)
{
	printf("%c\n", data->spawn_dir);
	if (data->spawn_dir == 'N')
	{
		vars->player.dir_x = 0;
		vars->player.dir_y = -1;
		vars->cam.planeX = 0.66;
		vars->cam.planeY = 0;
	}
	else if (data->spawn_dir == 'E')
	{
		vars->player.dir_x = 1;
		vars->player.dir_y = 0;
		vars->cam.planeX = 0;
		vars->cam.planeY = -0.66;
	}
	else if (data->spawn_dir == 'S')
	{
		vars->player.dir_x = 1;
		vars->cam.planeX = -0.66;
	}
	else if (data->spawn_dir == 'W')
	{
		vars->player.dir_x = -1;
		vars->player.dir_y = 0;
		vars->cam.planeX = 0;
		vars->cam.planeY = -0.66;	
	}
}

static void copy_data(t_vars *vars, t_data *data)
{
	vars->screen.screen_w = data->screen_x;
	vars->screen.screen_h = data->screen_y;

	vars->player.pos_x = data->spawn_pos_x;
	vars->player.pos_y = data->spawn_pos_y;
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

int parse_main(t_vars *vars, char *argv)
{
	t_data data;
	int i = 0;
	data.fd = open(argv, O_RDONLY);
	if (data.fd < 0)
		return (0);
	parse_init(&data);
	while (data.ret > 0 && data.error != -1)
	{
		i = 0;
		data.ret = get_next_line(data.fd, &data.line);
		if (data.ret < 0)
			return (ft_puterror("parse_main | get_next_line failed."));
		while (data.line[i] == ' ')
			i++;
		if (data.line[i] == 'R' && get_resolution(data.line, &data) == -1)
			data.error = -1;
		else if (data.line[i] == 'N')
		{
			i++;
			while (data.line[i] == ' ')
				i++;
			if (data.line[i] == 'O' && get_north(data.line, &data) == -1)
				data.error = -1;
		}
		else if (data.line[i] == 'E')
		{
			i++;
			while (data.line[i] == ' ')
				i++;
			if (data.line[i] == 'A' && get_east(data.line, &data) == -1)
				data.error = -1;
		}
		else if (data.line[i] == 'S')
		{
			i++;
			while (data.line[i] == ' ')
				i++;
			if (data.line[i] == 'O')
			{
				if (get_south(data.line, &data) == -1)			
				data.error = -1;
			}
			else
				if (get_sprite(data.line, &data) == -1)
					data.error = -1;
		}
		else if (data.line[i] == 'W')
		{
			i++;
			while (data.line[i] == ' ')
				i++;
			if (data.line[i] == 'E')
				get_west(data.line, &data);
		}
		else if (data.line[i] == 'C' && get_ceiling(data.line, &data) == -1)
			data.error = -1;
		else if (data.line[i] == 'F' && get_floor(data.line, &data) == -1)
			data.error = -1;
		else if (data.line[i] == '0' || data.line[i] == '1')
		{
			read_map(data.line, &data.map_width, &data.map_height, &data.sprite_count);
			if (data.map_start == -1)
				data.map_start = data.count;
		}
		free(data.line);
		data.count++;
		if (data.error == -1)
			return (parse_free(&data));
	}
	close(data.fd);
	if (data.map_start == -1)
	{
		ft_puterror("map missing.\n");
		return (parse_free(&data));
	}
	if (copy_map(&data, argv) == -1)
		return (parse_free(&data));
	if (!check_path(&data, data.spawn_pos_y, data.spawn_pos_x, 0))
	{
		ft_puterror("invalid map.\n");
		return (parse_free(&data));
	}
	transfer_map(&data);
	if (!missing_elem(&data))
	{
		ft_puterror("element missing.\n");
		return (parse_free(&data));
	}
	copy_data(vars, &data);
	return (data.error);
}