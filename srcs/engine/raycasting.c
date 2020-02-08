/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:37:04 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 20:16:50 by nlecaill    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

float short_dist(t_data *data)
{
	float  dist_h;
	float  dist_v;
	float  correct_dist;
	
	dist_v = linear_intersec_v(data);
	dist_h = linear_intersec_h(data);
	if (dist_h < dist_v)
	{
		correct_dist = dist_h;
		data->raycast.face_detect = 'H';
		data->raycast.inter.x = data->raycast.interH.x;
		data->raycast.inter.y = data->raycast.interH.y;
	}
	else
	{
		correct_dist = dist_v;
		data->raycast.face_detect = 'V';
	}
	if ((data->raycast.alpha < data->player.pov))
		data->raycast.beta = data->player.pov - data->raycast.alpha;
	else
		data->raycast.beta = data->raycast.alpha - data->player.pov;
	correct_dist *= (cosf(data->raycast.beta));
	return(correct_dist);
}

int scan(t_data *data)
{
	actionscontrol(data);
	mlx_clear_window(data->mlx.ptr, data->mlx.win);
	data->raycast.column = data->screen.size.x;
	data->raycast.alpha = data->player.pov - (data->player.fov / 2); // REVIEW optimiser

	while (data->raycast.column >= 0)
	{
		data->raycast.alpha += data->raycast.delta_ang; // REVIEW optimiser
		if (data->raycast.alpha >= _2PI) // REVIEW optimiser
			data->raycast.alpha -= _2PI; // REVIEW optimiser
		if (data->raycast.alpha < 0)
			data->raycast.alpha += _2PI; // REVIEW optimiser
		data->raycast.dist = short_dist(data);
		fill_column(data);
		data->raycast.column--;
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->image.img, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->Vtex.img, data->screen.size.x / 2 - 12, data->screen.size.y / 2 - 12);
	if (data->player.show_minimap)
		minimap(data);
	return (1);
}