/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   garbage.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 19:29:16 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int destroy(t_data *data)
{
	int i;

	i = -1;
	while (++i < HUD_TEX)
		mlx_destroy_image(data->mlx.ptr, data->hud_tex[i].img);
	i = 0;
	while (++i < OBJ_TEX)
		mlx_destroy_image(data->mlx.ptr, data->object[i].img);
	i = 0;
	while (++i < W_TEX)
		mlx_destroy_image(data->mlx.ptr, data->w_tex[i].img);
	mlx_destroy_image(data->mlx.ptr, data->image.img); //TODO destroy toute les textures
	mlx_destroy_window(data->mlx.ptr, data->mlx.win);
	wrdestroy();
	exit(1);
}
