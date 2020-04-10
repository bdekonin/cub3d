# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/06 18:06:17 by bdekonin      #+#    #+#                  #
#    Updated: 2020/04/10 15:03:54 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

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
	engine/pixels/fill_background.c \
	engine/pixels/my_pixel_put.c \
	engine/keys/key.c \
	engine/keys/walking.c \
	engine/render/wallsides.c \
	parsing/gather_sprite.c \
	engine/render/create_image.c \
	engine/bmp/createbmp.c \
	engine/keys/look.c \
	parsing/sortsprite.c \
	engine/sprite/sprite.c \
	engine/render/rayhit.c \
	engine/render/calculatedraw.c \
	engine/render/draw_wall.c \
	engine/render/side.c \
	engine/render/step.c \
	engine/render/main_render.c \
	engine/sprite/sort.c \
	parsing/read_filepath.c \
	parsing/gather_texture.c \
	parsing/read_map.c \
	parsing/parse_select.c

OBJ = $(SRC:.c=.o)
CC = gcc -Wall -Wextra -Werror
FLAGS = -L. -lmlx -framework OpenGL -framework AppKit
MLX = libmlx.dylib
LIB = libft/libft.a
INCLUDES = cub3D.h

all: $(NAME)

libmlx.dylib:
	@cd mlx && make && mv libmlx.dylib ..

$(NAME): $(OBJ) $(MLX)
	@$(MAKE) -C libft bonus
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB) 
	
%.o: %.c
	$(CC) -Imlx -Iinc -Ilibft -c $< -o $@

.PHONY: clean fclean re

norm:
	norminette $(SRC) $(INCLUDES)
	
clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f *~
	@/bin/rm -f .DS_Store
	@$(MAKE) -C libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C libft fclean
	
re: fclean all