# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 14:46:21 by hnagashi          #+#    #+#              #
#    Updated: 2025/06/07 23:35:35 by hnagashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux
LIBMLX = ./minilibx-linux
MLX_FLAGS = -L$(LIBMLX) -lmlx -lX11 -lXext -lm
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

SRC = src/main.c src/utils/utils.c src/utils/utils2.c src/utils/utils3.c src/utils/utils4.c\
		src/render/ray.c src/render/render.c src/render/find.c src/render/shadow.c src/render/light.c\
		src/parse/parse.c src/parse/parse_ambient.c src/parse/parse_camera.c \
		src/parse/parse_cylinder.c src/parse/parse_light.c src/parse/parse_plane.c src/parse/parse_sphere.c \
		src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c \
		src/hit/hit.c src/hit/hit_cylinder.c \
		src/key_hook/key_hook.c src/key_hook/key_hook_utils.c \
		src/vec3/vec3.c src/vec3/vec3_utils.c src/vec3/vec3_basic.c \

SRC_BONUS = src_bonus/main_bonus.c \
		src_bonus/vec3/vec3_basic_bonus.c src_bonus/vec3/vec3_utils_bonus.c src_bonus/vec3/vec3_bonus.c \
		src_bonus/render/ray_bonus.c src_bonus/render/find_bonus.c src_bonus/render/light_bonus.c src_bonus/render/render_bonus.c src_bonus/render/shadow_bonus.c src_bonus/render/checker_bonus.c src_bonus/render/checker_cy_bonus.c\
		src_bonus/hit/hit_bonus.c src_bonus/hit/hit_cylinder_bonus.c \
		src_bonus/parse/parse_bonus.c src_bonus/parse/parse_sphere_bonus.c src_bonus/parse/parse_light_bonus.c \
		src_bonus/parse/parse_plane_bonus.c src_bonus/parse/parse_camera_bonus.c src_bonus/parse/parse_cylinder_bonus.c src_bonus/parse/parse_ambient_bonus.c\
		src_bonus/utils/utils_bonus.c src_bonus/utils/utils2_bonus.c src_bonus/utils/utils3_bonus.c src_bonus/utils/utils4_bonus.c \
		src_bonus/key_hook/key_hook_utils_bonus.c src_bonus/key_hook/key_hook_bonus.c \
		src_bonus/get_next_line/get_next_line_bonus.c src_bonus/get_next_line/get_next_line_utils_bonus.c \

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = miniRT
NAME_BONUS = miniRT_bonus


$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)/libmlx.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) $(LIBFT_FLAGS) 

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT) $(LIBMLX)/libmlx.a
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(MLX_FLAGS) $(LIBFT_FLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX)/libmlx.a:
	make -C $(LIBMLX)


all: $(NAME)
bonus: $(NAME_BONUS)


clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus