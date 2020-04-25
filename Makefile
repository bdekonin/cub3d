# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/06 18:06:17 by bdekonin      #+#    #+#                  #
#    Updated: 2020/04/25 15:57:14 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NOCOLOR = \033[0m
MAGENTA = \033[35m

NAME = cub3D

SRC = main.c utils.c \
	get_next_line/get_next_line.c \
	parsing/flood_map.c \
	parsing/gather_color_value.c \
	parsing/gather_map.c \
	parsing/gather_resolution.c \
	parsing/parse_init.c \
	parsing/parse_main.c \
	parsing/parse_utils.c \
	parsing/sortsprite.c \
	parsing/gather_sprite.c \
	parsing/read_filepath.c \
	parsing/gather_texture.c \
	parsing/read_map.c \
	parsing/parse_select.c \
	engine/pixels/fill_background.c \
	engine/pixels/my_pixel_put.c \
	engine/keys/key.c \
	engine/keys/walking.c \
	engine/keys/look.c \
	engine/render/rayhit.c \
	engine/render/wallsides.c \
	engine/render/create_image.c \
	engine/render/calculatedraw.c \
	engine/render/draw_wall.c \
	engine/render/side.c \
	engine/render/step.c \
	engine/render/main_render.c \
	engine/sprite/sprite.c \
	engine/sprite/sort.c \
	engine/bmp/createbmp.c

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -L. -lmlx -framework OpenGL -framework AppKit
MLX = libmlx.dylib
LIBFT = libft/libft.a
INCLUDES = cub3d.h

bonus: all

all: $(NAME)

libmlx.dylib:
	@echo "$(MAGENTA)[cub3d] - Compiling $(MLX).$(NOCOLOR)"
	@cd mlx && make && mv $(MLX) ..

$(NAME): $(OBJ) $(MLX)
	@$(MAKE) -C libft
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(MAGENTA)[cub3d] - Compiled an cub3D executable.$(NOCOLOR)"

%.o: %.c
	@$(CC) -Imlx -Iinc -Ilibft -c $< -o $@

norm:
	norminette $(SRC) $(INCLUDES) libft

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f .DS_Store
	@$(MAKE) -C libft clean
	@$(MAKE) -C mlx clean
	@/bin/rm -f save.bmp
	@echo "$(MAGENTA)[cub3d] - Removed All excess files.$(NOCOLOR)"

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@/bin/rm -f $(MLX)
	@echo "$(MAGENTA)[cub3d] - Removed libft's library and \
	cub3d executable.$(NOCOLOR)"

re: fclean all

.PHONY: clean fclean re
