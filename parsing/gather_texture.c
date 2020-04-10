/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_texture.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 12:34:25 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 13:28:58 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

int				get_north(char *line, t_data *data)
{
	if (data->malloced[0] == 'Y')
	{
		return (ft_puterror("get_north | multiple elements found."));
	}
	data->north_path = read_filepath(line);
	if (!data->north_path)
	{
		return (ft_puterror("get_north | malloc failed."));
	}
	else if (ft_strncmp(data->north_path, "file", 100) == 0)
	{
		return (ft_puterror("get_north | file could not be opened / found."));
	}
	data->malloced[0] = 'Y';
	return (1);
}

int				get_east(char *line, t_data *data)
{
	if (data->malloced[2] == 'Y')
	{
		return (ft_puterror("get_east | multiple elements found."));
	}
	data->east_path = read_filepath(line);
	if (!data->east_path)
	{
		return (ft_puterror("get_east | malloc failed."));
	}
	else if (ft_strncmp(data->east_path, "file", 100) == 0)
	{
		return (ft_puterror("get_east | file could not be opened / found."));
	}
	data->malloced[2] = 'Y';
	return (1);
}

int				get_south(char *line, t_data *data)
{
	if (data->malloced[1] == 'Y')
	{
		return (ft_puterror("get_south | multiple elements found."));
	}
	data->south_path = read_filepath(line);
	if (!data->south_path)
	{
		return (ft_puterror("get_south| malloc failed."));
	}
	else if (ft_strncmp(data->south_path, "file", 100) == 0)
	{
		return (ft_puterror("get_south | file could not be opened / found."));
	}
	data->malloced[1] = 'Y';
	return (1);
}

int				get_west(char *line, t_data *data)
{
	if (data->malloced[3] == 'Y')
	{
		return (ft_puterror("get_west | multiple elements found."));
	}
	data->west_path = read_filepath(line);
	if (!data->west_path)
	{
		return (ft_puterror("get_west | malloc failed."));
	}
	else if (ft_strncmp(data->west_path, "file", 100) == 0)
	{
		return (ft_puterror("get_west | file could not be opened / found."));
	}
	data->malloced[3] = 'Y';
	return (1);
}

int				get_sprite(char *line, t_data *data)
{
	if (data->malloced[4] == 'Y')
	{
		return (ft_puterror("get_sprite | multiple elements found."));
	}
	data->sprite_path = read_filepath(line);
	if (!data->sprite_path)
	{
		return (ft_puterror("get_sprite | malloc failed."));
	}
	else if (ft_strncmp(data->sprite_path, "file", 100) == 0)
	{
		return (ft_puterror("get_sprite | file could not be opened / found."));
	}
	data->malloced[4] = 'Y';
	return (1);
}
