/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/26 18:56:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 23:43:53 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../libft/includes/libft.h"
# include "../libmlx/mlx.h"
# include "raycast.h"
# include "player.h"
# include <math.h>

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		height;
}				t_data;
# include "world.h"

double	linear_intersec_h(t_world *world, t_raycast *raycast);
double	linear_intersec_v(t_world *world, t_raycast *raycast);

# endif