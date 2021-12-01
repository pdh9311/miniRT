CC			:= gcc
CFLAGS		:= -g -Werror -Wextra -Wall
CHECK		:=	-fsanitize=address

OS 			:= $(shell uname)
ifeq ($(OS), Linux)
	MLX_DIR		:= ../minilibx-linux/
	MLX			:= -lm -lXext -lX11
else
	MLX_DIR		:= ../minilibx/
	MLX			:= -lm -framework OpenGL -framework AppKit
endif

MLX_LIB = $(MLX_DIR)libmlx.a
MLX_INC = $(MLX_DIR)

.PHONY		: all clean fclean re

$(MLX_LIB) :
	@$(MAKE) -sC $(MLX_DIR)

0 : $(MLX_LIB)
	@$(CC) rgb.c -o rgb -L$(MLX_DIR) -lmlx $(MLX) -I$(MLX_INC)

1 : $(MLX_LIB)
	@$(CC) vector.c -o vector -L$(MLX_DIR) -lmlx $(MLX) -I$(MLX_INC)

2 : $(MLX_LIB)
	@$(CC) ray_camera.c -o ray_camera -L$(MLX_DIR) -lmlx $(MLX) -I$(MLX_INC)

3 : $(MLX_LIB)
	@$(CC) sphere.c -o sphere -L$(MLX_DIR) -lmlx $(MLX) -I$(MLX_INC)

4 : $(MLX_LIB)
	@$(CC) normal.c -o normal -L$(MLX_DIR) -lmlx $(MLX) -I$(MLX_INC)

5 : $(MLX_LIB)
	@$(CC) hit_record.c -o hit_record -L$(MLX_DIR) -lmlx $(MLX) -I$(MLX_INC)

# @$(MAKE) clean -sC $(MLX_DIR)
clean :
	@rm -rf rgb
	@rm -rf ray
	@rm -rf circle
	@rm -rf sphere
	@rm -rf normal
	@rm -rf hit
