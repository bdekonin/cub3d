/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 12:16:36 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/06 21:21:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** This will create an image for the correct filetype.
** It will also set all the nessecary items to the correct value's.
*/

int		file_sprite(t_vars *vars)
{
	char *p;

	p = ft_strrchr(vars->cub.sprite, '.');
	if (ft_strncmp(p, ".png", 5) == 0)
		vars->tex.img[4] = mlx_png_file_to_image(vars->mlx.mlx, \
		vars->cub.sprite, &vars->tex.w[4], &vars->tex.h[4]);
	else if (ft_strncmp(p, ".xpm", 5) == 0)
		vars->tex.img[4] = mlx_xpm_file_to_image(vars->mlx.mlx, \
		vars->cub.sprite, &vars->tex.w[4], &vars->tex.h[4]);
	else
		return (ft_puterror("Sprite file is not a png nor a xpm file."));
	if (!vars->tex.img[3])
		return (ft_puterror("Sprite image could not be created."));
	vars->tex.addr[4] = mlx_get_data_addr(vars->tex.img[4], \
	&vars->tex.bits_pixel[4], &vars->tex.line_length[4], \
	&vars->tex.endian[4]);
	if (!vars->tex.addr[4])
		return (ft_puterror("Sprite adress could not be retrieved."));
	return (1);
}

int		file_west(t_vars *vars)
{
	char *p;

	p = ft_strrchr(vars->cub.west, '.');
	if (ft_strncmp(p, ".png", 5) == 0)
		vars->tex.img[3] = mlx_png_file_to_image(vars->mlx.mlx, \
		vars->cub.west, &vars->tex.w[3], &vars->tex.h[3]);
	else if (ft_strncmp(p, ".xpm", 5) == 0)
		vars->tex.img[3] = mlx_xpm_file_to_image(vars->mlx.mlx, \
		vars->cub.west, &vars->tex.w[3], &vars->tex.h[3]);
	else
		return (ft_puterror("West file is not a png nor a xpm file."));
	if (!vars->tex.img[3])
		return (ft_puterror("West image could not be created."));
	vars->tex.addr[3] = mlx_get_data_addr(vars->tex.img[3], \
	&vars->tex.bits_pixel[3], &vars->tex.line_length[3], \
	&vars->tex.endian[3]);
	if (!vars->tex.addr[3])
		return (ft_puterror("West adress could not be retrieved."));
	return (1);
}

int		file_south(t_vars *vars)
{
	char *p;

	p = ft_strrchr(vars->cub.south, '.');
	if (ft_strncmp(p, ".png", 5) == 0)
		vars->tex.img[2] = mlx_png_file_to_image(vars->mlx.mlx, \
		vars->cub.south, &vars->tex.w[2], &vars->tex.h[2]);
	else if (ft_strncmp(p, ".xpm", 5) == 0)
		vars->tex.img[2] = mlx_xpm_file_to_image(vars->mlx.mlx, \
		vars->cub.south, &vars->tex.w[2], &vars->tex.h[2]);
	else
		return (ft_puterror("South file is not a png nor a xpm file."));
	if (!vars->tex.img[2])
		return (ft_puterror("South image could not be created."));
	vars->tex.addr[2] = mlx_get_data_addr(vars->tex.img[2], \
	&vars->tex.bits_pixel[2], &vars->tex.line_length[2], \
	&vars->tex.endian[2]);
	if (!vars->tex.addr[2])
		return (ft_puterror("South adress could not be retrieved."));
	return (1);
}

int		file_east(t_vars *vars)
{
	char *p;

	p = ft_strrchr(vars->cub.east, '.');
	if (ft_strncmp(p, ".png", 5) == 0)
		vars->tex.img[1] = mlx_png_file_to_image(vars->mlx.mlx, \
		vars->cub.east, &vars->tex.w[1], &vars->tex.h[1]);
	else if (ft_strncmp(p, ".xpm", 5) == 0)
		vars->tex.img[1] = mlx_xpm_file_to_image(vars->mlx.mlx, \
		vars->cub.east, &vars->tex.w[1], &vars->tex.h[1]);
	else
		return (ft_puterror("East file is not a png nor a xpm file."));
	if (!vars->tex.img[1])
		return (ft_puterror("East image could not be created."));
	vars->tex.addr[1] = mlx_get_data_addr(vars->tex.img[1], \
	&vars->tex.bits_pixel[1], &vars->tex.line_length[1], \
	&vars->tex.endian[1]);
	if (!vars->tex.addr[1])
		return (ft_puterror("East adress could not be retrieved."));
	return (1);
}

int		file_north(t_vars *vars)
{
	char *p;

	p = ft_strrchr(vars->cub.north, '.');
	if (ft_strncmp(p, ".png", 5) == 0)
		vars->tex.img[0] = mlx_png_file_to_image(vars->mlx.mlx, \
		vars->cub.north, &vars->tex.w[0], &vars->tex.h[0]);
	else if (ft_strncmp(p, ".xpm", 5) == 0)
		vars->tex.img[0] = mlx_xpm_file_to_image(vars->mlx.mlx, \
		vars->cub.north, &vars->tex.w[0], &vars->tex.h[0]);
	else
		return (ft_puterror("North file is not a png nor a xpm file."));
	if (!vars->tex.img[0])
		return (ft_puterror("North image could not be created."));
	vars->tex.addr[0] = mlx_get_data_addr(vars->tex.img[0], \
	&vars->tex.bits_pixel[0], &vars->tex.line_length[0], \
	&vars->tex.endian[0]);
	if (!vars->tex.addr[0])
		return (ft_puterror("North adress could not be retrieved."));
	return (1);
}
