/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 15:29:10 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 11:05:22 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"
#include "../cub3d.h"

int		missing_elem(t_data *data)
{
	if (data->malloced[0] == 'N' || data->malloced[1] == 'N' ||
	data->malloced[2] == 'N' || data->malloced[3] == 'N' ||
	data->malloced[4] == 'N' || data->malloced[5] == 'N' ||
	data->floor[0] == -1 || data->ceiling[0] == -1 || data->res[0] == 'N')
		return (0);
	return (1);
}

void		transfer_map(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (data->map[y][x] == 8)
				data->map[y][x] = 0;
			if (data->map[y][x] == 7)
				data->map[y][x] = 2;
			if (data->map[y][x] == 6)
				data->map[y][x] = 3;
			x++;
		}
		y++;
		x = 0;
	}
}

size_t		ft_strlen_nospace(char *s)
{
	size_t i;
	size_t len;

	len = ft_strlen(s);
	i = len - 1;
	while (s[i] == ' ')
	{
		s[i] = '\0';
		i--;
	}
	return (len);
}

int			parse_free(t_data *data)
{
	if (data->malloced[0] == 'Y')
		free(data->north_path);
	if (data->malloced[1] == 'Y')
		free(data->south_path);
	if (data->malloced[2] == 'Y')
		free(data->east_path);
	if (data->malloced[3] == 'Y')
		free(data->west_path);
	if (data->malloced[4] == 'Y')
		free(data->sprite_path);
	if (data->malloced[5] == 'Y')
	{
		// free_map(data, data->map_height);
		free_array((void*)data->map, data->map_height);
		free(data->map);
	}
	if (data->sprite_count > 0)
	{
		free_sprites(data, data->sprite_count);
		free(data->sprite);
	}
	return (-1);
}

int free_array(void **arr, int count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	return (-1);
}
