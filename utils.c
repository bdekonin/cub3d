/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 19:22:53 by bdekonin       #+#    #+#                */
/*   Updated: 2020/02/19 14:30:11 by bdekonin      ########   odam.nl         */
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
