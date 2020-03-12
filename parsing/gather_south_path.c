/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_south_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:34:28 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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
