/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:37:04 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:30:51 by dgascon     ###    #+. /#+    ###.fr     */
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
		data->raycast.inter.x = data->raycast.inter_h.x;
		data->raycast.inter.y = data->raycast.inter_h.y;
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

void	put_text_to_screen(t_data *data)
{
	static int timer = -1;
	static int a = 0;

	char text[2][50] = {" ", "doors unlocked"};
	if (data->world.locked == 0 && data->world.was_lock == 1 && a ==0)
	{
		a = 1;
		data->world.was_lock = 0;
		timer++;
	}
	if (timer != -1)
	{
		mlx_string_put(data->mlx.ptr, data->mlx.win, 50, 50, 0xff0000, text[a]);
		timer++;
		if (timer > 50)
		{
			timer = -1;
			a = 0;
		}
	}
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
		if (data->raycast.alpha >= 2 * M_PI) // REVIEW optimiser
			data->raycast.alpha -= 2 * M_PI; // REVIEW optimiser
		if (data->raycast.alpha < 0)
			data->raycast.alpha += 2 * M_PI; // REVIEW optimiser
		data->raycast.dist = short_dist(data);
		fill_column(data);
		data->raycast.column--;
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->image.img, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->vtex.img, data->screen.size.x / 2 - 12, data->screen.size.y / 2 - 12);
	
	if (data->player.show_minimap)
		minimap(data);
	put_text_to_screen(data);
	return (1);
}