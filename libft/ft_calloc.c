/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 09:01:26 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 10:33:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (count * size));
	if (!str)
		return (NULL);
	else
	{
		while (i != (count * size))
		{
			str[i] = 0;
			i++;
		}
		return (str);
	}
}
