/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_sprite_path.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:21:47 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:39:11 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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
