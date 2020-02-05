/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   garbage.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 17:18:07 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int destroy(t_data *data)
{
	mlx_destroy_image(data->mlx.ptr, data->Ftex.img);
	mlx_destroy_image(data->mlx.ptr, data->Vtex.img);
	mlx_destroy_image(data->mlx.ptr, data->Wtex.img);
	mlx_destroy_image(data->mlx.ptr, data->Rtex.img);
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
		free(data->world.map[i]);
		i++;
	}
}
