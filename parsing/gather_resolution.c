/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_resolution.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 16:20:37 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/17 17:06:47 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static int		read_resolution(char *line, int *x, int *y)
{
	while (*line == 'R' || *line == ' ')
		line++;
	*x = ft_atoi(line);
	while (ft_isdigit(*line) && *line != '\0')
		line++;
	while (*line == ' ')
		line++;
	*y = ft_atoi(line);
	if (*x > 0 && *y > 0)
		return (1);
	return (-1);
}

int				get_resolution(char *line, t_data *data)
{
	if (data->screen_x > 0 && data->screen_y > 0)
	{
		return (ft_puterror("get_resolution | multiple elements found."));
	}
	if (read_resolution(line, &data->screen_x, &data->screen_y) == -1)
	{
		return (ft_puterror("get_resolution | invalid resolution."));
	}
	data->screen_x = (data->screen_x > 2880) ? 2880 : data->screen_x;
	data->screen_y = (data->screen_y > 1620) ? 1620 : data->screen_y;
	data->res[0] = 'Y';
	return (1);
}
