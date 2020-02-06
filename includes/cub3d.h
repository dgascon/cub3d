/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/26 18:56:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 20:29:30 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"
# include "../libmlx/mlx.h"
# include <math.h>
# include "screen.h"
# include "world.h"
# include "player.h"
# include "raycast.h"

# define _2PI 2 * M_PI
# define _3PI_2 3 * M_PI_2

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct s_lsprite
{
	t_coord pos;
	t_coord grd;
	int		visible;
	int		printed;
	float	dist;
	void *next;
}				t_lsprite;

typedef	struct 	s_image
{
	void	*img;
	char	*add_image;
	int		bpp;
	int		size_line;
	int 	endian;
	int 	colors;
	int		sizex;
	int		sizey;
}				t_image;

typedef	struct 	s_actions
{
	enum e_boolean forward;
	enum e_boolean backward;
	enum e_boolean leftward;
	enum e_boolean rightward;
	enum e_boolean lookleft;
	enum e_boolean lookright;
	enum e_boolean lookup;
	enum e_boolean lookdown;
	enum e_boolean speed;
	enum e_boolean crouching;
	enum e_boolean jump;
}				t_actions;

typedef	struct 	s_data
{
	t_mlx		mlx;
	t_screen	screen;
	t_world		world;
	t_player	player;
	t_raycast	raycast;
	t_image		image;
	t_image		Wtex;
	t_image		Ftex;
	t_image		Rtex;
	t_image		Vtex;
	t_actions	actions;
	t_image		barel;
	t_lsprite	*lst;
	int test;
}				t_data;

void			mlx_rect(t_data *data, t_coord pos, t_coord size, int colors);
void    		mlx_line(t_data *data, t_coord start, t_coord end, int colors);
int 			scan(t_data *data);
void    		actionscontrol(t_data *data);
void			minimap(t_data *data, int width, int height);
t_lsprite		*lsprite_new(t_coord pos);
int				set_visible(t_lsprite *list, t_coord grid);
t_lsprite		*pick_object(t_lsprite *list, t_coord grid);
void			print_floor_and_ceil(t_data *data, int row, int	gnagna, int height_proj_plane, int h_max);

# endif