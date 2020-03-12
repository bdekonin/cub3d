/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_west_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:40:28 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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
