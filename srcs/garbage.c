/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   garbage.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 13:51:11 by nlecaill    ###    #+. /#+    ###.fr     */
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
	exit(0);
}
