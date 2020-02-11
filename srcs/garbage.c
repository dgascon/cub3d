/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   garbage.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:30:51 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int destroy(t_data *data)
{
	mlx_destroy_image(data->mlx.ptr, data->ftex.img);
	mlx_destroy_image(data->mlx.ptr, data->vtex.img);
	mlx_destroy_image(data->mlx.ptr, data->wtex.img);
	mlx_destroy_image(data->mlx.ptr, data->rtex.img);
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
