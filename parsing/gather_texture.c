/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_texture.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 12:34:25 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/21 22:24:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

int				get_north(char *line, t_data *data)
{
	if (data->malloced[0] == 'Y')
	{
		return (ft_puterror("Found multiple North elements."));
	}
	data->north_path = read_filepath(line);
	if (!data->north_path)
	{
		return (ft_puterror("Something went wrong recieving the North path"));
	}
	else if (ft_strncmp(data->north_path, "file", 100) == 0)
	{
		return (ft_puterror("North file couldn't be found or opened."));
	}
	data->malloced[0] = 'Y';
	return (1);
}

int				get_east(char *line, t_data *data)
{
	if (data->malloced[2] == 'Y')
	{
		return (ft_puterror("Found multiple East elements."));
	}
	data->east_path = read_filepath(line);
	if (!data->east_path)
	{
		return (ft_puterror("Something went wrong recieving the East path."));
	}
	else if (ft_strncmp(data->east_path, "file", 100) == 0)
	{
		return (ft_puterror("East file couldn't be found or opened."));
	}
	data->malloced[2] = 'Y';
	return (1);
}

int				get_south(char *line, t_data *data)
{
	if (data->malloced[1] == 'Y')
	{
		return (ft_puterror("Found multiple South elements."));
	}
	data->south_path = read_filepath(line);
	if (!data->south_path)
	{
		return (ft_puterror("Something went wrong recieving the South path."));
	}
	else if (ft_strncmp(data->south_path, "file", 100) == 0)
	{
		return (ft_puterror("South file couldn't be found or opened."));
	}
	data->malloced[1] = 'Y';
	return (1);
}

int				get_west(char *line, t_data *data)
{
	if (data->malloced[3] == 'Y')
	{
		return (ft_puterror("Found multiple West elements."));
	}
	data->west_path = read_filepath(line);
	if (!data->west_path)
	{
		return (ft_puterror("Something went wrong recieving the West path."));
	}
	else if (ft_strncmp(data->west_path, "file", 100) == 0)
	{
		return (ft_puterror("West file couldn't be found or opened."));
	}
	data->malloced[3] = 'Y';
	return (1);
}

int				get_sprite(char *line, t_data *data)
{
	if (data->malloced[4] == 'Y')
	{
		return (ft_puterror("Found multiple Sprite elements."));
	}
	data->sprite_path = read_filepath(line);
	if (!data->sprite_path)
	{
		return (
	ft_puterror("Something went wrong recieving the Sprite path."));
	}
	else if (ft_strncmp(data->sprite_path, "file", 100) == 0)
	{
		return (ft_puterror("Sprite file couldn't be found or opened."));
	}
	data->malloced[4] = 'Y';
	return (1);
}
