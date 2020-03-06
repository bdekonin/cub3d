/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createbmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 13:34:03 by bdekonin       #+#    #+#                */
/*   Updated: 2020/03/06 17:44:22 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int createbmpimage(t_vars *vars, int fd)
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
			color = *(unsigned int*)(vars->mlx.addr + (y * 
			vars->mlx.line_length + x * (vars->mlx.bits_pixel / 8)));
			write(fd, &color, 3);
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
	header[0] = 0x42; // B
	header[1] = 0x4D; // M
	ft_memcpy(header + 2, &filesize, 4); // 2 - 6
	header[10] = 54; // 10 - 14 | pixeldataoffset
	header[14] = 40;
	ft_memcpy(header + 18, &vars->screen.screen_w, 4);
	ft_memcpy(header + 22, &vars->screen.screen_h, 4);
	header[26] = 1; // planes
	header[28] = 24; // bits per pixel
	write (fd, header, 54);
	return (0);
}

int createbmp(t_vars *vars)
{
	int fd;
	int filesize;
	int padding;
	renderframe(vars);
	fd = open("save.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	padding = (4 - (vars->screen.screen_w  * 3) % 4) % 4;
			printf("padding = %d\n", padding);
	filesize = 54 + 3 * (vars->screen.screen_w + padding) * vars->screen.screen_h;
	 	   printf("size = %d\n", filesize);
	createheader(vars, fd, filesize);
	createbmpimage(vars, fd);
	return (1);
}