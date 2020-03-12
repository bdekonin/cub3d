/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_east_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:10:21 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:37:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

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
