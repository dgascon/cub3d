# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/07 15:11:52 by dgascon      #+#   ##    ##    #+#        #
#    Updated: 2020/02/13 16:33:56 by dgascon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY:	all clean fclean re

NAME		=	libft.a

PATH_INC	=	includes
PATH_SRC	=	srcs
PATH_OBJ	=	objs

SRC_LIST	= 	string/ft_strlen.c		string/ft_toupper.c				\
				string/ft_tolower.c		string/ft_atoi.c				\
				string/ft_isascii.c		string/ft_isprint.c				\
				string/ft_isalpha.c		string/ft_isdigit.c				\
				string/ft_isalnum.c		string/ft_strchr.c				\
				string/ft_strrchr.c		string/ft_strncmp.c				\
				string/ft_strlcpy.c		string/ft_strlcat.c				\
				string/ft_strnstr.c		string/ft_strstr.c				\
				string/ft_strdup.c		string/ft_substr.c				\
				string/ft_strjoin.c		string/ft_strtrim.c				\
				string/ft_split.c		string/ft_strmapi.c				\
				string/ft_strcat.c		string/ft_strichr.c				\
				string/ft_chartostr.c	string/ft_charstr.c				\
				string/ft_strcmp.c										\
				string/ft_delcharstr.c									\
				mem/ft_memset.c			mem/ft_bzero.c					\
				mem/ft_memcpy.c			mem/ft_memccpy.c				\
				mem/ft_memmove.c		mem/ft_memchr.c					\
				mem/ft_memcmp.c			mem/ft_calloc.c					\
				mem/ft_wrmalloc.c 										\
				put/ft_putchar_fd.c		put/ft_putcharec_fd.c			\
				put/ft_putstr_fd.c		put/ft_putendl_fd.c				\
				put/ft_putnbr_fd.c		put/ft_putnbr_base_fd.c			\
				put/ft_putnstr_fd.c		put/ft_putnbr_ui_base_fd.c		\
				put/ft_putnbr_format_fd.c								\
				put/ft_message.c										\
				lists/ft_lstnew.c		lists/ft_lstadd_front.c			\
				lists/ft_lstsize.c		lists/ft_lstlast.c				\
				lists/ft_lstadd_back.c	lists/ft_lstdelone.c			\
				lists/ft_lstclear.c		lists/ft_lstiter.c				\
				lists/ft_lstmap.c										\
				gnl/get_next_line.c		gnl/get_next_line_utils.c		\
				maths/ft_power.c		maths/ft_sqrt.c	maths/ft_abs.c	\
				numbers/ft_digit.c		numbers/ft_digit_base.c			\
				numbers/ft_digit_ul_base.c numbers/ft_itoa.c			\
				numbers/ft_itoa_base.c	numbers/ft_digit_format_base.c	\
				utils/ft_base.c			utils/colors.c					\
				ftprintf/ft_printf.c	ftprintf/pf_conv.c				\
				ftprintf/pf_utils.c		ftprintf/lists/pf_initlst.c		\
				ftprintf/display/pf_disp_char.c							\
				ftprintf/display/pf_disp_int.c 							\
				ftprintf/display/pf_disp_perc.c 						\
				ftprintf/display/pf_disp_ptr.c 							\
				ftprintf/display/pf_disp_string.c 						\
				ftprintf/display/pf_disp.c

INCS_LIST	=	libft.h libftenum.h libftgnl.h libftlst.h libftmaths.h libftmem.h libftnumbers.h libftprintf.h libftput.h libftstring.h

OBJS		=	$(addprefix $(PATH_OBJ)/, $(SRC_LIST:.c=.o))
INCS		=	$(addprefix $(PATH_INC)/, $(INCS_LIST))

CC			=	gcc
INCLUDES	=	-I$(PATH_INC)
CFLAGS		=	-Wall -Wextra -Werror
C-O			=	$(CC) $(CFLAGS) $(PF_LIB) $(INCLUDES) -c $< -o $@

DIRS_LIST	= mem put lists string utils gnl maths numbers ftprintf ftprintf/display ftprintf/lists

all: $(NAME)
	@ printf "\r                                                                                          \r"

$(NAME): $(OBJS) $(INCS)
	@ ar rc $(NAME) $(OBJS)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(INCS)
	@ $(shell mkdir -p $(PATH_OBJ) $(addprefix $(PATH_OBJ)/, $(DIRS_LIST)))
	@ printf "\033[0;38;5;198mCompilation de \033[1m$< ..."
	@ $(C-O)
	@ printf "\r                                                                                          \r"

clean:
	@ /bin/rm -rf $(PATH_OBJ)
	
fclean: clean
	@ /bin/rm -f $(NAME) ./a.out
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(PATH_OBJ) ..."
	@ sleep 0.2
	@ printf "\r                                                                                          \r"
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(NAME) ..."
	@ sleep 0.2
	@ printf "\r                                                                                          \r"
	@ printf "\033[0;38;5;82mSuppression des fichiers de compilation reussis pour la \033[1mlibft.\n"

re: fclean all
