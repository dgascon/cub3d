# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/07 15:11:52 by dgascon      #+#   ##    ##    #+#        #
#    Updated: 2020/02/13 14:32:39 by dgascon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY:	all clean fclean re

NAME			=	Cub3d

PATH_INC		=	includes

PATH_SRC		=	srcs
PATH_OBJ		=	objs
SRC_LIST		= 	engine/raycasting.c engine/render.c engine/linear_intersec.c 	\
					engine/mlx_geometrical.c	engine/floor_and_ceil.c				\
					engine/textures.c												\
					parsing/parse.c	parsing/minimap.c parsing/parse_param.c			\
					keycontrol/actionscontrol.c keycontrol/keypress.c				\
					keycontrol/keyreleased.c										\
					garbage.c lst.c player.c move.c world.c

INCS_LIST		=	cub3d.h player.h world.h raycast.h screen.h

OBJS			=	$(addprefix $(PATH_OBJ)/, $(SRC_LIST:.c=.o))
OBJS_BONUS		=	$(addprefix $(PATH_OBJ)/, $(BONUS_LIST:.c=.o))
INCS			=	$(addprefix $(PATH_INC)/, $(INCS_LIST))

LIBFT_PATH		=	libft
LIBFT_NAME		=	libft.a
LIBFT_FLAG 		=	-Llibft -lft
LIBFT_LIB 		= 	$(FLAG_FT)
LIBFT_INC		=	$(addprefix $(LIBFT_PATH)/, $(PATH_INC))
LIBFT			=	$(addprefix $(LIBFT_PATH)/, $(LIBFT_NAME))

MINILIBX_PATH	= 	libmlx
MINILIBX_NAME	= 	libmlx.a

CC				=	gcc
INCLUDES		=	-I$(LIBFT_INC) -I$(MINILIBX_PATH) -I$(PATH_INC)
CFLAGS			=	-Wall -Wextra # REVIEW Add -Werror
C-O				=	$(CC) $(CFLAGS) -D DEBUG=$(DEBUG) $(LIBFT_LIB) $(INCLUDES) -c $< -o $@

DIRS_LIST	= engine parsing keycontrol

all $(DEBUG):	$(LIBFT_NAME) $(MINILIBX_NAME) $(NAME)
	@ printf "\033[0;38;5;82mCompilation de \033[1mCub3D \033[0;38;5;82mreussis.\n\033[0m"

$(NAME): $(OBJS) $(INCS) comp

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(INCS)
	@ $(shell mkdir -p $(PATH_OBJ) $(addprefix $(PATH_OBJ)/, $(DIRS_LIST)))
	@ printf "\033[0;38;5;198mCompilation de $< ..."
	@ $(C-O)
	@ printf "\r                                                                                          \r\033[0m"

$(LIBFT_NAME):
	@ make -C $(LIBFT_PATH)
	@ printf "\033[0;38;5;82mCompilation de la \033[1m$@ \033[0;38;5;82mreussis.\n\033[0m"

$(MINILIBX_NAME):
	@ printf "\033[0m"
	@ make -C $(MINILIBX_PATH)
	@ printf "\033[0;38;5;82mCompilation de la \033[1m$@ \033[0;38;5;82mreussis.\n\033[0m"

clean:
	@ /bin/rm -rf $(PATH_OBJ)
	@ make -C $(LIBFT_PATH) clean
	@ make -C $(MINILIBX_PATH) clean

cleanperso:
	@ /bin/rm -rf $(PATH_OBJ)

fclean: clean
	@ make -C $(LIBFT_PATH) fclean
	@ /bin/rm -rf $(NAME) ./$(NAME)*
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(PATH_OBJ) ..."
	@ sleep 0.5
	@ printf "\r                                                                                          \r\033[0m"
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(NAME) ..."
	@ sleep 0.5
	@ printf "\r                                                                                          \r\033[0m"
	@ printf "\033[0;38;5;82mSuppression des fichiers de compilation reussis pour \033[1mCub3D.\n"

comp:
	@ $(CC) $(CFLAGS) -O2 -o $(NAME) libmlx/libmlx.a libft/libft.a $(OBJS) -framework OpenGL -framework AppKit main.c

re: fclean all
