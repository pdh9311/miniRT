C			:= gcc
CFLAGS		:= -g -Werror -Wextra -Wall
CHECK		:=	-fsanitize=address

OS 			:= $(shell uname)
ifeq ($(OS), Linux)
	MLX_DIR	:= ../minilibx-linux/
	MLX		:= -lm -lXext -lX11
else
	MLX_DIR	:= ../minilibx/
	MLX		:= -lm -framework OpenGL -framework AppKit
endif

all :
	@echo "input: make [tester]"

window :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX)
	@./$@

image :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX)
	@./$@

discontinuous_keyhook :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX)
	@./$@

continuous_keyhook :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX)
	@./$@

discontinuous_mousehook_1 :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX)
	@./$@

discontinuous_mousehook_2 :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX)
	@./$@

closehook :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX) -I./
	@./$@

bresenham :
	@gcc $@.c -o $@ -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(MLX) -I./
	@./$@

clean :
	rm -rf window \
	image \
	discontinuous_keyhook continuous_keyhook \
	discontinuous_mousehook_1 discontinuous_mousehook_2 \
	closehook \
	bresenham
