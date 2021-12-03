TARGET		:= test

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra -ggdb -O0
MLX_FLAG	:= -lm -lmlx -framework OpenGL -framework AppKit

MLX_DIR		:= ../minilibx
MLX			:= $(MLX_DIR)/libmlx.a

SRC_DIR		:= ./
SRC_FILE	:= main.c
SRCS		:= $(addprefix $(SRC_DIR), $(SRC_FILE))

OBJ_DIR		:= ./
OBJ_FILE	:= $(SRC_FILE:.c=.o)
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJ_FILE))

SRCS_DIR	:=	../source/
SOURCES		:=	readfile.c \
				types/type_a.c \
				types/type_c.c \
				types/type_l.c \
				types/type_pl.c \
				types/type_sp.c \
				types/type_cy.c \
				types/utils.c \
				utils/free.c \
				list/pp_lstnew.c \
				list/pp_lstadd_front.c \
				list/pp_lstadd_back.c \
				list/pp_lstsize.c \
				list/pp_lstlast.c \
				list/pp_lstdelone.c \
				ray_tracing/camera.c \
				ray_tracing/color.c \
				ray_tracing/hittable_list_1.c \
				ray_tracing/hittable_list_2.c \
				ray_tracing/hittable.c \
				ray_tracing/material.c \
				ray_tracing/moving_sphere.c \
				ray_tracing/ray.c \
				ray_tracing/rtweekend.c \
				ray_tracing/sphere.c \
				ray_tracing/vec3-1.c \
				ray_tracing/vec3-2.c \
				ray_tracing/vec3-3.c \
				ray_tracing/vec3-4.c \
				ray_tracing/vec3-5.c \
				ray_tracing/vec3-6.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))

.PHONY		: all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -L$(MLX_DIR) -o $@ $(MLX_FLAG)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@ -I../minilibx -I../include

1 : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

2 : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

ray_test : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

normal : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

sphere_test : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

sphere_test2 : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

two_sphere : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

sphere_move : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

sphere_move2 : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

antialiase : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

diffuse : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

diffuse_move : fclean
	$(CC) $(CFLAGS) -c $(SRCS) -I../include -I./stuff
	$(CC) $(CFLAGS) -c $@.c -I../include -I./stuff
	$(CC) -o $@ *.o -I../include -I./stuff -L./stuff $(MLX_FLAG) -lft
	rm *.o

clean :
	@rm -f *.o
	@echo "Removed OBJS"

fclean : clean
	@rm -f $(TARGET)
	@rm -f 1
	@rm -f 2
	@rm -f ray_test
	@rm -f normal
	@rm -f sphere_test
	@rm -f sphere_test2
	@rm -f two_sphere
	@rm -f sphere_move
	@rm -f sphere_move2
	@rm -f antialiase
	@rm -f diffuse
	@rm -f diffuse_move
	@echo "fclean Done!!"