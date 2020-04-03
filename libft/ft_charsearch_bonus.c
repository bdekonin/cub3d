/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_charsearch_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:12:22 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/13 13:13:26 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_charsearch(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
