/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastienlecaille <sebastienlecaille@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 10:39:33 by dgascon           #+#    #+#             */
/*   Updated: 2022/02/11 17:05:05 by sebastienle      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libmlx/mlx.h"
# include <math.h>
# include <pthread.h>

struct s_data;

typedef struct s_data t_data;

# include "screen.h"
# include "world.h"
# include "player.h"
# include "raycast.h"

# define OBJ_TEX 10
# define W_TEX 6
# define HUD_TEX 1

# define NB_THREAD 10

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef	struct	s_image
{
	void		*img;
	char		*add_image;
	int			bpp;
	int			size_line;
	int			endian;
	int			colors;
	t_coord		size;
	int			valid;
	char		*path;
}				t_image;

typedef struct	s_lsprite
{
	t_coord		pos;
	t_coord		grd;
	t_coord		detect_position;
	int			visible[NB_THREAD];
	int			printed;
	float		dist;
	void		*next;
	t_image		texture;
}				t_lsprite;

typedef struct	s_floor
{
	float		dist;
	t_coord		pos;
	t_f_coord	delta;
}				t_floor;

struct	s_data
{
	t_mlx		mlx;
	t_screen	screen;
	t_world		world;
	t_player	player;
	t_raycast	raycast;
	t_image		image;
	t_actions	actions;
	t_lsprite	*lst;
	t_image		w_tex[W_TEX];
	t_image		hud_tex[HUD_TEX];
	t_image		obj_tex[OBJ_TEX];
	int			th_num;
	int			bmp_save;
};

int				init_texture(t_data *data, t_image *image);
int				dup_path(t_image *image, char *line);
void			mlx_rect(t_image *image, t_coord pos, t_coord size, int colors);
int				scan(t_data *data);
int				minimap(t_data *data);
int				set_visible(t_lsprite *list, t_coord grid);
t_lsprite		*pick_object(t_lsprite *list, t_coord grid);
t_lsprite		*lsprite_new(t_coord pos, t_image texture);
void			lsprite_addback(t_lsprite **lst, t_lsprite *new);
void			lsprite_sort(t_lsprite **lst);
void			pt_floor_ceil(t_data *data, int row, int qte_mur_sous_hdv,
					int height_proj_plane);
void			save_bmp(t_data *data);
int				floor_ceil_color(t_data *data, float c_const[4],
					int qte_mur_sur_hdv, int *val2);
int				darken_wall(float dist, int val);
int				destroy(t_data *data);

#endif
