/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_select.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 15:01:47 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/21 22:21:47 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static int		line_select_map(t_data *data, int i)
{
	if (data->line[i] == '0' || data->line[i] == '1' || data->line[i] == '2')
	{
		read_map(data->line, &data->map_width, \
									&data->map_height, &data->sprite_count);
		if (data->map_start == -1 && (ft_counter(data->line, '1') \
									+ ft_counter(data->line, '0') > 0))
			data->map_start = data->count;
	}
	else if (data->line[i] == '\0' && i > 1)
		return (ft_puterror("Invalid line."));
	return (1);
}

int				line_select(t_data *data, int i)
{
	if (data->line[i] == 'R')
		return (get_resolution(data->line + 1, data));
	else if (data->line[i] == 'N' && data->line[i + 1] == 'O')
		return (get_north(data->line + i + 2, data));
	else if (data->line[i] == 'E' && data->line[i + 1] == 'A')
		return (get_east(data->line + i + 2, data));
	else if (data->line[i] == 'S' && data->line[i + 1] == 'O')
		return (get_south(data->line + i + 2, data));
	else if (data->line[i] == 'S' && data->line[i + 1] == ' ')
		return (get_sprite(data->line + i + 1, data));
	else if (data->line[i] == 'W' && data->line[i + 1] == 'E')
		return (get_west(data->line + i + 2, data));
	else if (data->line[i] == 'C')
		return (get_ceiling(data->line + i, data));
	else if (data->line[i] == 'F')
		return (get_floor(data->line + i, data));
	return (line_select_map(data, i));
}

int				parse_error_check(t_data *data, char *argv)
{
	if (data->map_start == -1)
	{
		ft_puterror("No map found.");
		return (parse_free(data));
	}
	if (copy_map(data, argv) == -1)
		return (parse_free(data));
	if (!check_path(data, data->spawn_pos_y, data->spawn_pos_x, 0))
	{
		ft_puterror("Flood fill has failed.");
		return (parse_free(data));
	}
	transfer_map(data);
	if (!missing_elem(data))
	{
		ft_puterror("Missing an element.");
		return (parse_free(data));
	}
	return (1);
}
