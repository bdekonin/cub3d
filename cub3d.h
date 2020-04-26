/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 19:15:35 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/26 08:04:15 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "parsing/parse_data.h"
# include "mlx/mlx.h"

# define MOVESPEED 0.09
# define ROTATESPEED 0.05

typedef struct			s_key
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					esc;
	int					l_arr;
	int					r_arr;
}						t_key;

typedef struct			s_camera
{
	double				planex;
	double				planey;
	double				rot_speed;
	double				move_speed;
	double				camera_x;
}						t_camera;

typedef struct			s_mlx
{
	void				*mlx;
	void				*mlx_win;
	void				*img;
	char				*addr;
	int					bits_pixel;
	int					line_length;
	int					endian;
}						t_mlx;

typedef struct			s_nextframe
{
	void				*img;
	char				*addr;
	int					bits_pixel;
	int					line_length;
	int					endian;
}						t_nextframe;

typedef struct			s_south
{
	void				*img;
	char				*addr;
	int					bits_pixel;
	int					line_length;
	int					endian;
	int					w;
	int					h;
}						t_south;

typedef struct			s_texture
{
	void				*img[6];
	char				*addr[6];
	int					bits_pixel[6];
	int					line_length[6];
	int					endian[6];
	int					w[6];
	int					h[6];
	char				w_tex;
}						t_texture;

typedef struct			s_screen
{
	int					screen_w;
	int					screen_h;
}						t_screen;

typedef struct			s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
}						t_player;

typedef struct			s_map
{
	int					**map;
	int					map_w;
	int					map_h;
	int					pos_x;
	int					pos_y;
}						t_map;

typedef struct			s_cub
{
	int					floor_color;
	int					ceiling_color;
	char				*north;
	char				*east;
	char				*south;
	char				*west;
	char				*sprite;
}						t_cub;

typedef struct			s_engine
{
	double				raydir_x;
	double				raydir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
}						t_engine;

typedef struct			s_sprite
{
	double				**sprite;
	double				sprite_x;
	double				sprite_y;
	double				invdet;
	double				transform_x;
	double				transform_y;
	double				*zbuffer;
	int					sprite_count;
	int					texwidth;
	int					texheight;
	int					spritescreenx;
	int					spriteheight;
	int					drawstart_y;
	int					drawstart_x;
	int					spritewidth;
	int					drawend_y;
	int					drawend_x;
}						t_sprite;

typedef struct			s_render
{
	double				step;
	double				tex_pos;
	double				wall_x;
	int					tex_x;
	int					tex_y;
	int					lineheight;
	int					drawstart;
	int					drawend;
}						t_render;

typedef struct			s_vars
{
	t_screen			screen;
	t_map				map;
	t_cub				cub;
	t_mlx				mlx;
	t_key				key;
	t_player			player;
	t_camera			cam;
	t_texture			tex;
	t_engine			eng;
	t_sprite			spr;
	t_nextframe			nframe;
	t_render			ren;
	short				image;
	short				save;
	unsigned int		color;
	int					ret;
	char				*file_ext;
}						t_vars;

/*
** Render
** senddir | Also has the search hit function.
*/
int						engine(t_vars *vars);
int						frame_loop(t_vars *vars);
int						initialize_rendering(t_vars *vars);
void					renderframe(t_vars *vars);
void					senddir(t_vars *vars);
void					calculatedraw(t_vars *vars);
void					draw_wall(t_vars *vars, int x);
void					side(t_vars *vars);
void					step(t_vars *vars);
void					wallsides(t_vars *vars);

/*
**	Coloring
*/
void					fill_background(int x, int start, \
										int end, t_vars *vars);
void					my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

/*
**	Key function
*/
int						key_press(int keycode, t_vars *vars);
int						key_release(int keycode, t_vars *vars);
int						close_win(t_vars *vars);
void					init_key(t_vars *vars);

/*
** Movement
*/
void					forward(t_vars *vars);
void					backwards(t_vars *vars);
void					look_left(t_vars *vars);
void					look_right(t_vars *vars);
void					walk_right(t_vars *vars);
void					walk_left(t_vars *vars);

/*
** Parsing
** Returns -1 if something went wrong else 1
*/
int						parse_main(t_vars *vars, char *argv);
int						file_north(t_vars *vars);
int						file_east(t_vars *vars);
int						file_south(t_vars *vars);
int						file_west(t_vars *vars);
int						file_sprite(t_vars *vars);

/*
** Screenshot
*/
int						createbmp(t_vars *vars);

/*
** Sprite
*/
void					sprite(t_vars *vars, int i);
void					sort_sprites(t_vars *vars);

/*
** Etc
*/
int						ft_puterror(char *s);
#endif
