/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 13:14:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 15:03:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_DATA_H
# define PARSE_DATA_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../cub3d.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../cub3d.h"

typedef struct	s_data
{
	char		*line;
	int			fd;
	int			ret;
	int			screen_x;
	int			screen_y;
	char		res[1];
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	char		*sprite_path;
	int			floor[3];
	int			ceiling[3];
	int			error;
	int			map_width;
	int			map_height;
	int			map_start;
	int			count;
	int			spawn_pos_x;
	int			spawn_pos_y;
	char		spawn_dir;
	int			**map;
	char		malloced[7];
	int			sprite_count;
	double		**sprite;
}				t_data;

/*
** Recieving information
*/
int				get_resolution(char *line, t_data *data);
int				get_north(char *line, t_data *data);
int				get_east(char *line, t_data *data);
int				get_south(char *line, t_data *data);
int				get_west(char *line, t_data *data);
int				get_sprite(char *line, t_data *data);
int				get_floor(char *line, t_data *data);
int				get_ceiling(char *line, t_data *data);
char			*read_filepath(char *line);
size_t			ft_strlen_nospace(char *s);
int				line_select(t_data *data, int i);

/*
** map
*/
void			read_map(char *line, int *width, int *height, int *sprite);
int				*fill_line(int width);
void			transfer_map(t_data *data);
int				copy_map(t_data *data, char *argv);
int				replace_map(t_data *data, char *argv);
int				free_map(t_data *data, int i);

/*
** sprites
*/
int				free_sprites(t_data *data, int i);
int				free_array(void **arr, int count);
void			save_sprite(t_data *data, int y, int x);
void			calculate_dist(t_data *data);
int				make_sprite(t_data *data);

/*
** flood filling
*/
int				check_next(t_data *data, int row, int col, int prev);
int				check_path(t_data *data, int row, int col, int prev);

/*
** etc
*/
int				missing_elem(t_data *data);
int				parse_free(t_data *data);
void			parse_init(t_data *data);
int				parse_error_check(t_data *data, char *argv);
#endif
