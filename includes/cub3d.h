/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/26 18:56:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:40:31 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"
# include "../libmlx/mlx.h"
# include <math.h>
#include <pthread.h>
# include "screen.h"
# include "world.h"
# include "player.h"
# include "raycast.h"

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct s_pi
{
	float dPI;
	float tPId;
}				t_pi;
typedef struct s_lsprite
{
	t_coord pos;
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
	int		size;
}				t_image;

typedef	struct 	s_key
{
	enum e_boolean arrow_left;
	enum e_boolean arrow_right;
	enum e_boolean arrow_up;
	enum e_boolean arrow_down;
	enum e_boolean incspeed;
	enum e_boolean decspeed;
	enum e_boolean D;
	enum e_boolean A;
	enum e_boolean S;
	enum e_boolean W;
	enum e_boolean SQUAT;
	enum e_boolean JUMP;
}				t_key;

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
	t_key		key;
	t_pi		pi;
	t_image		barel;
	t_lsprite	*lst;
	int test;
}				t_data;

int 	scan(t_data *data);
int 	move_up(t_data *data, float dir);
int 	move_down(t_data *data, float dir);
void	mlx_rect(t_data *data, t_coord pos, t_coord size, int colors);
void    mlx_line(t_data *data, t_coord start, t_coord end, int colors);
void	minimap(t_data *data, int width, int height);

# endif