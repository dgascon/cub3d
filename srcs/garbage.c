/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   garbage.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 18:59:12 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int destroy(t_data *data)
{
	mlx_destroy_image(data->mlx.ptr, data->w_tex[4].img);
	mlx_destroy_image(data->mlx.ptr, data->hud_tex[0].img);
	mlx_destroy_image(data->mlx.ptr, data->w_tex[0].img);
	mlx_destroy_image(data->mlx.ptr, data->w_tex[1].img);
	mlx_destroy_image(data->mlx.ptr, data->w_tex[2].img);
	mlx_destroy_image(data->mlx.ptr, data->w_tex[3].img);
	mlx_destroy_image(data->mlx.ptr, data->w_tex[5].img);
	mlx_destroy_image(data->mlx.ptr, data->image.img); //TODO destroy toute les textures
	mlx_destroy_window(data->mlx.ptr, data->mlx.win);
	exit(1);
}

void freemap(t_data *data, int offset)
{
	int i;

	i = 0;
	while (i < data->world.size.y - offset)
	{
		wrfree(data->world.map[i]);
		i++;
	}
}
