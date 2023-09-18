#---COMMON_VAR-----------------------------------
NAME			=	cub3d
CC				=	cc
FLAGS			=	-Wall -Werror -Wextra
MLX_FLAGS		=	-lmlx -lXext -lX11
RM				=	rm -rf
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
NC				=	\033[0m
#---LIBFT_VAR-------------------------------------
LIBFT_PATH		=	libft/
LIBFT_NAME		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
#---CUB_VAR---------------------------------------
SRC				=	main.c \
					parse.c	
OBJS_DIR		=	.OBJS/
OBJS			=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER_DIR		=	headers/
HEADER_FILE		=	headers/cub3d.h \
					headers/struct.h

#---MINILIBX-------------------------------------
MLX_PATH		=	minilibx
MINILIBX		=	$(MLX_PATH)/libmlx.a
#---RULES----------------------------------------

$(NAME):		$(OBJS_DIR) $(LIBFT) Makefile $(HEADER_FILE) $(OBJS)
				@$(CC) $(FLAGS) -g -I $(HEADER_DIR) -I $(MLX_PATH) $(OBJS) -lm $(MLX_FLAGS) $(LIBFT) -o $@
				@echo "\33[2K\r$(GREEN)Cub3d compiled :D$(NC)"


$(OBJS_DIR)%.o:	%.c $(HEADER_FILE)
				@$(CC) $(FLAGS) -g -I $(HEADER_DIR) -I $(MLX_PATH) -lm $(MLX_FLAGS) -c $< -o $@
				@echo -n "\33[2K\r$(YELLOW)Compiled $<"

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)srcs

all:			$(NAME)

norm:
				@norminette $(SRC) $(HEADER_DIR) | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(NC)"}'

$(LIBFT):
				@echo "$(YELLOW)\nCOMPILING $(LIBFT_PATH)\n"
				@make -sC $(LIBFT_PATH)
				@echo "$(GREEN)LIBFT created\n$(NC)"

$(MINILIBX):
				@make -sC minilibx

clean:
				@echo "$(RED)Deleting Obj file in $(LIBFT_PATH)...\n"
				@make clean -sC $(LIBFT_PATH)
				@make clean -sC $(MLX_PATH)
				@echo "$(GREEN)Done\n"
				@echo "$(RED)Deleting cub3d object...\n"
				@$(RM) $(OBJS_DIR)
				@echo "$(GREEN)Done\n"

fclean:			clean
				@echo "$(RED)Deleting cub3d executable..."
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_PATH)
				@make fclean -C $(MLX_PATH)
				@echo "$(GREEN)Done\n"

re:				fclean all

.PHONY:			all clean fclean re
