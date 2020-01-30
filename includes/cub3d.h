/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/26 18:56:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 14:12:49 by dgascon     ###    #+. /#+    ###.fr     */
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
	double dPI;
	double tPId;
}				t_pi;

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
}				t_data;

int scan(t_data *data);
int move_up(t_data *data, double dir);
int move_down(t_data *data, double dir);
# endif