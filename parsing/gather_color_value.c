/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gather_color_value.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 17:32:40 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/12 09:50:09 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

static void		parse_rgb(char *line, int *r, int *g, int *b)
{
	if (*line == ',')
		line++;
	while (*b == -1 && *line == ' ' && *line != '\0')
		line++;
	if (*line == ' ')
		*line = '\0';
	*r = ft_atoi(line);
	while (ft_isdigit(*line) && *line != '\0')
		line++;
	if (*g == -1 && *b == -1)
		parse_rgb(line, g, b, r);
	else if (*g == -1)
		parse_rgb(line, g, r, b);
	*r = (*r > 255) ? -255 : *r;
	*g = (*g > 255) ? -255 : *g;
	*b = (*b > 255) ? -255 : *b;
}

int				get_floor(char *line, t_data *data)
{
	line++;
	if (*line != ' ')
		return (ft_puterror("get_floor | invalid rgb value."));
	while (*line == ' ' && *line != '\0')
		line++;
	if (!ft_isdigit(*line) || ft_strsearch(line, " ,0123456789") == 0)
		return (ft_puterror("get_floor | invalid character found in line."));
	if (data->floor[0] >= 0 && data->floor[1] >= 0 && data->floor[2] >= 0)
	{
		return (ft_puterror("get_floor | multiple elements found."));
	}
	if (ft_counter(line, ',') == 2)
		parse_rgb(line, &data->floor[0], &data->floor[1], &data->floor[2]);
	data->floor[0] = (ft_counter(line, ',') == 2) ? data->floor[0] : -1;
	if (data->floor[0] < 0 || data->floor[1] < 0 || data->floor[2] < 0)
	{
		return (ft_puterror("get_floor | invalid rgb value."));
	}
	return (1);
}

int				get_ceiling(char *line, t_data *data)
{
	line++;
	while (*line == ' ' && *line != '\0')
		line++;
	if (!ft_isdigit(*line) || ft_strsearch(line, " ,0123456789") == 0)
		return (ft_puterror("get_ceiling | invalid character found in line."));
	if (data->ceiling[0] >= 0 && data->ceiling[1] >= 0 && data->ceiling[2] >= 0)
	{
		return (ft_puterror("get_ceiling | multiple elements found."));
	}
	if (ft_counter(line, ',') == 2)
		parse_rgb(line, &data->ceiling[0], &data->ceiling[1], \
		&data->ceiling[2]);
	data->ceiling[0] = (ft_counter(line, ',') == 2) ? data->ceiling[0] : -1;
	if (data->ceiling[0] < 0 || data->ceiling[1] < 0 || data->ceiling[2] < 0)
	{
		return (ft_puterror("get_ceiling | invalid rgb value."));
	}
	return (1);
}
