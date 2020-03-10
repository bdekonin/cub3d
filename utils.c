/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 19:22:53 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/09 20:57:29 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	ft_puterror(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	return (-1);
}

int		ft_strsearch(char *line, char *str)
{
	int i;
	int j;

	i = 0;
	while (line[i] != '\0')
	{
		j = 0;
		while (str[j] != '\0')
		{
			if (str[j] == line[i])
				break ;
			j++;
			if (str[j] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}