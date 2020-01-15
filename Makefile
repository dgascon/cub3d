# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/07 15:11:52 by dgascon      #+#   ##    ##    #+#        #
#    Updated: 2020/01/13 14:52:56 by dgascon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY:	all clean fclean re

NAME			=	Cube3d

PATH_INC		=	includes

PATH_SRC		=	srcs
PATH_OBJ		=	objs
SRC_LIST		= 	player.c world.c engine/linear_intersec.c engine/render.c

INCS_LIST		=	cube3d.h player.h world.h raycast.h

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

all:	$(LIBFT_NAME) $(MINILIBX_NAME) $(NAME)

$(NAME): $(OBJS) $(INCS) comp	

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(INCS)
	@ $(shell mkdir -p $(PATH_OBJ) $(PATH_OBJ)/engine)
	@ $(C-O)
	@ echo "\033[32m V \033[1m$<\033[0;32m\t| \033[1m$@ create !\033[0m"
	@ echo " \033[36m--CMD-- \033[32m$(C-O) create !\033[0m"

$(LIBFT_NAME):
	@ make -C $(LIBFT_PATH)
	@ echo "\033[33;1m-- -- -- Compilation de la libft réussis. -- -- --\033[0m"

$(MINILIBX_NAME):
	@ make -C $(MINILIBX_PATH)
	@ echo "\033[33;1m-- -- -- Compilation de la minilibx réussis. -- -- --\033[0m"

clean:
	@ /bin/rm -rf $(PATH_OBJ)
	@ make -C $(LIBFT_PATH) clean
	@ make -C $(MINILIBX_PATH) clean

fclean: clean
	@ /bin/rm -rf $(NAME) ./a.out*
	@ echo "\033[31m > \033[1m$(NAME)/$(PATH_OBJ)/*\033[0;31m delete.\033[0m"
	@ echo "\033[31m > \033[1m$(NAME)/$(NAME)\033[0;31m delete.\033[0m"
	@ make -C $(LIBFT_PATH) fclean
	@ echo "-----------------------------------------"

comp:
	@ $(CC) $(CFLAGS) -o $(NAME) libmlx/libmlx.a libft/libft.a $(OBJS) -framework OpenGL -framework AppKit tests/main_1.c

re: fclean all
