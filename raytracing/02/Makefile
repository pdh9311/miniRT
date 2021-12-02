C			:= gcc
CFLAGS		:= -g -Werror -Wextra -Wall
CHECK		:=	-fsanitize=address

OS 			:= $(shell uname)
ifeq ($(OS), Linux)
	MLX_DIR		:= ./minilibx-linux/
	MLX			:= -lm -lXext -lX11
else
	MLX_DIR		:= ./minilibx/
	MLX			:= -lm -framework OpenGL -framework AppKit -lc
endif

MLX_LIB = $(MLX_DIR)libmlx.a
MLX_INC = $(MLX_DIR)

LIBFT_DIR	:= ./libft/
LIBFT_LIB	:= $(LIBFT_DIR)libft.a
LIBFT_INC	:= $(LIBFT_DIR)

INC_DIR		:= ./include/
INCLUDES	:= minirt.h keycode.h keyhook.h \
				vec3.h rtweekend.h color.h \
				ray.h
INCS		:= $(addprefix $(INC_DIR), $(INCLUDES))

SRCS_DIR	:=	./source/
SOURCES		:=	minirt.c keyhook.c 02_ray.c \
				vec3.c rtweekend.c color.c \
				ray.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))

OBJS_DIR	:=	./object/
OBJECTS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJECTS))

LIBRARY		:= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(MLX)
HEADERS		:= -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX_INC)

NAME		:= tutorial

.PHONY		: all clean fclean re

$(NAME) : $(LIBFT_LIB) $(MLX_LIB) $(OBJS_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBRARY) $(HEADERS)

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) -c $? -o $@ $(CFLAGS) $(HEADERS)

$(LIBFT_LIB) :
	@$(MAKE) -sC $(LIBFT_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)

$(MLX_LIB) :
	@$(MAKE) -sC $(MLX_DIR)

all : $(NAME)

clean :
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@$(MAKE) clean -sC $(MLX_DIR)
	@rm -rf $(OBJS_DIR)

fclean : clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -f $(NAME)

re : fclean all
