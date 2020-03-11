/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createbmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 13:34:03 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/11 15:09:10 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	createbmpimage(t_vars *vars, int fd, int padding)
{
	int color;
	int y;
	int x;

	y = vars->screen.screen_h;
	while (y > 0)
	{
		x = 0;
		while (x < vars->screen.screen_w)
		{
			color = *(unsigned int*)(vars->mlx.addr + (y * \
			vars->mlx.line_length + x * (vars->mlx.bits_pixel / 8)));
			if (write(fd, &color, 3) < 0)
				return (ft_puterror("Write failed while writing in bmp."));
			if (padding == 1 && write(fd, "\0", 1) < 0)
				return (ft_puterror("Write failed while writing in bmp."));
			if (padding == 2 && write(fd, "\0\0", 2) < 0)
				return (ft_puterror("Write failed while writing in bmp."));
			if (padding == 3 && write(fd, "\0\0\0", 3) < 0)
				return (ft_puterror("Write failed while writing in bmp."));
			x++;
		}
		y--;
	}
	return (1);
}

static int createheader(t_vars *vars, int fd, int filesize)
{
	unsigned char header[54];

	ft_bzero(header, 54);
	header[0] = 0x42;
	header[1] = 0x4D;
	ft_memcpy(header + 2, &filesize, 4);
	header[10] = 54;
	header[14] = 40;
	ft_memcpy(header + 18, &vars->screen.screen_w, 4);
	ft_memcpy(header + 22, &vars->screen.screen_h, 4);
	header[26] = 1;
	header[28] = 24;
	if (write (fd, header, 54) < 0)
		return (ft_puterror("Could not write header in 'save.bmp' file."));
	return (1);
}

int createbmp(t_vars *vars)
{
	int fd;
	int filesize;
	int padding;

	renderframe(vars);
	fd = open("save.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		return (ft_puterror("Could not create 'save.bmp' file."));
	padding = (4 - (vars->screen.screen_w  * 3) % 4) % 4;
	filesize = 54 + 3 * (vars->screen.screen_w + padding) * vars->screen.screen_h;
	if (createheader(vars, fd, filesize) == -1)
		return (-1);
	if (createbmpimage(vars, fd, padding) == -1)
		return (-1);
	return (1);
}