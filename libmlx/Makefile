#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

all: $(NOM)
	@ printf "\r                                                                                          \r"

$(NOM):	$(OBJ)
	@ ar -rc $(NOM) $(OBJ)
	@ ranlib $(NOM)

%.o: %.m
	@ cc $(CFLAGS) -c $< -o $@

%.o: %.c
	@ printf "\033[0;38;5;198mCompilation de \033[1m$< ..."
	@ cc $(CFLAGS) -c $< -o $@
	@ printf "\r                                                                                          \r"

clean:
	@ rm -f $(NOM) $(OBJ) *~
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NOM) ..."
	@ sleep 0.2
	@ printf "\r                                                                                          \r"
	@ rm -f mlx_app
	@ printf "\033[0;38;5;160mSuppression des \033[1mobjets ..."
	@ sleep 0.2
	@ printf "\r                                                                                          \r"
	@ printf "\033[0;38;5;160mSuppression de \033[1m*~ ..."
	@ sleep 0.2
	@ printf "\r                                                                                                                                                                                 \r"
	@ printf "\033[0;38;5;82mSuppression des fichiers de compilation reussis pour la \033[1mlibmlx.\n"

re: clean all
