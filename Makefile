# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/07 15:11:52 by dgascon      #+#   ##    ##    #+#        #
#    Updated: 2020/01/17 16:48:27 by dgascon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY:	all clean fclean re

NAME			=	Cube3d

PATH_INC		=	includes

PATH_SRC		=	srcs
PATH_OBJ		=	objs
SRC_LIST		= 	world.c engine/linear_intersec.c engine/render.c

INCS_LIST		=	cube3d.h player.h world.h raycast.h window.h

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
C-O				=	$(CC) $(CFLAGS) $(LIBFT_LIB) $(INCLUDES) -c $< -o $@

DIRS_LIST	= engine

all:	$(LIBFT_NAME) $(MINILIBX_NAME) $(NAME)


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

fclean: clean
	@ make -C $(LIBFT_PATH) fclean
	@ /bin/rm -rf $(NAME) ./a.out*
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(PATH_OBJ) ..."
	@ sleep 0.5
	@ printf "\r                                                                                          \r\033[0m"
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(NAME) ..."
	@ sleep 0.5
	@ printf "\r                                                                                          \r\033[0m"
	@ printf "\033[0;38;5;82mSuppression des fichiers de compilation reussis pour \033[1mCub3D.\n"

comp:
	@ $(CC) $(CFLAGS) -o $(NAME) libmlx/libmlx.a libft/libft.a $(OBJS) -framework OpenGL -framework AppKit tests/main_1.c

re: fclean all
