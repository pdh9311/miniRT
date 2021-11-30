TARGET		:= test

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra
MLX_FLAG	:= -lm -lmlx -framework OpenGL -framework AppKit

MLX_DIR		:= ../minilibx
MLX			:= $(MLX_DIR)/libmlx.a

SRC_DIR		:= ./
SRC_FILE	:= main.c
SRCS		:= $(addprefix $(SRC_DIR), $(SRC_FILE))

OBJ_DIR		:= ./
OBJ_FILE	:= $(SRC_FILE:.c=.o)
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJ_FILE))

.PHONY		: all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -L$(MLX_DIR) -o $@ $(MLX_FLAG)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@ -I../minilibx -I../include

1 :
	$(CC) $(CFLAGS) $@.c -o $@ -I../include -L$(MLX_DIR) $(MLX_FLAG)

2 :
	$(CC) $(CFLAGS) $@.c -o $@ -I../include -L$(MLX_DIR) $(MLX_FLAG)

normal : fclean
	$(CC) $(CFLAGS) $@.c -o $@ -I../include -L$(MLX_DIR) $(MLX_FLAG)

sphere : fclean
	$(CC) $(CFLAGS) $@.c -o $@ -I../include -L$(MLX_DIR) $(MLX_FLAG)

sphere_move : fclean
	$(CC) $(CFLAGS) $@.c -o $@ -I../include -L$(MLX_DIR) $(MLX_FLAG)

ray : fclean
	$(CC) $(CFLAGS) $@.c -o $@ -I../include -L$(MLX_DIR) $(MLX_FLAG)	

clean :
	@rm -f $(OBJS)
	@echo "Removed OBJS"

fclean : clean
	@rm -f $(TARGET)
	@rm -f ray
	@rm -f sphere
	@rm -f sphere_move
	@rm -f normal
	@rm -f 1
	@rm -f 2
	@echo "fclean Done!!"