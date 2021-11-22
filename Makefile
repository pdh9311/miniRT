C			:= gcc
CFLAGS		:= -g -Werror -Wextra -Wall
CHECK		:=	-fsanitize=address

OS 			:= $(shell uname)
USERS 		:= $(shell Users)
ifeq ($(OS), Linux)
#MLX_DIR		:= ./minilibx-linux/
#MLX			:= $(MATH_LIB) -lXext -lX11
else ifeq ($(USERS), joonpark)
MLX_DIR		:= ./minilibx/
MLX			:= -lm -framework OpenGL -framework AppKit
else ifeq ($(USERS), donpark)
MLX_DIR		:=
MLX			:=
endif

MLX_LIB = $(MLX_DIR)libmlx.a
MLX_INC = $(MLX_DIR)

LIBFT_DIR	:= ./libft/
LIBFT_LIB	:= $(LIBFT_DIR)libft.a
LIBFT_INC	:= $(LIBFT_DIR)

INC_DIR		:= ./include/
INCLUDES	:= miniRT.h
INCS		:= $(addprefix $(INC_DIR), $(INCLUDES))

SRCS_DIR	:=	./source/
SOURCES		:=	main.c
SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))

OBJS_DIR	:=	./object/
OBJECTS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJECTS))

LIBRARY		:= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx
HEADERS		:= -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX_INC)

NAME		:= miniRT

# colors
RED			:=	\033[31m
GREEN 		:=	\033[32m
YELLOW 		:=	\033[33m
BLUE 		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
WHITE		:=	\033[37m
PINK		:=	\033[38;5;201m
OBJS_DOT	:=	\033[38;5;201m\033[48;5;252m\033[1m\033[3m
MENT		:=	\033[38;5;191m\033[1m
RE_MENT		:=	\033[38;5;63m\033[1m
RESET		:=	\033[0m

.PHONY		: all clean fclean re bonus $(NAME)

$(NAME) : $(LIBFT_LIB) $(MLX_LIB) $(OBJS_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBRARY) $(HEADERS)
	@echo "\n$(GREEN)object files were created$(RESET)"
	@echo "$(RED)miniRT created.$(RESET)"

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)
	@echo "$(MENT)[ Created obj directory ... ]$(RESET)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) -c $< -o $@ $(CFLAGS) $(HEADERS)
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT_LIB) :
	@$(MAKE) -sC $(LIBFT_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@echo "$(YELLOW)[ Created libft.a ... ]$(RESET)"

$(MLX_LIB) :
	@$(MAKE) -sC $(MLX_DIR)
	@echo "$(YELLOW)[ Created libmlx.a ... ]$(NC)"

all : $(NAME)

clean :
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@$(MAKE) clean -sC $(MLX_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "$(MENT)[Removing object files]"
	@echo "$(MAGENTA)$(OBJS)$(RESET)"

fclean : clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(MENT)[Removing $(NAME)]$(RESET)"
	@echo "$(NAME):$(MAGENTA) deleted$(RESET)"

ment_re :
	@echo "$(RE_MENT)[make re]$(RESET)"

re : ment_re fclean all
	@echo "$(RE_MENT)[make re done.]$(RESET)"

norm :
	@echo "$(MENT)[Norminette test]$(RESET)"
	@find ./libft -name "*.c" -exec norminette {} \;
	@find ./libft -name "*.h" -exec norminette {} \;
	@echo "$(CYAN)\c"
	@find ./source -name "*.c" -exec norminette {} \;
	@find ./include -name "*.h" -exec norminette {} \;
	@echo "$(RESET)"