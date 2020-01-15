/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 11:37:48 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 14:50:13 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube3d.h"

void    put_column(int column, t_data *win, t_raycast *raycast)
{
	double	height;

	height = (64 / raycast->dist) * ((win->width / 2) / tan(M_PI / 6));
	while(height--)
	{
		mlx_pixel_put(win->mlx_ptr, win->mlx_win, column, height, 0xFF00FF);
	}
}