/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 11:37:48 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 23:02:57 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube3d.h"

void    put_column(t_data *data)
{
	double	height;

	height = (round(64 / data->world.player.ray.dist)) * round((round((data->window.width / 2)) / tan(M_PI / 6)));
	while(height--)
	{
		mlx_pixel_put(data->mlx.ptr, data->mlx.win, data->world.player.ray.column, height, 0xFF00FF);
	}
}