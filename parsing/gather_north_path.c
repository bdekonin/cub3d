/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_north_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:00:20 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:38:54 by bdekonin      ########   odam.nl         */
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
