/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:37:04 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 13:54:48 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

double short_dist(t_data *data)
{
    double  dist_h;
    double  dist_v;
    double  correct_dist;

    dist_h = linear_intersec_h(data);
	dist_v = linear_intersec_v(data);
	if (ft_abs_d(dist_h) < ft_abs_d(dist_v))
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
    if ((data->raycast.alpha > data->player.pov))
        data->raycast.beta = data->player.pov - data->raycast.alpha;
	else
        data->raycast.beta = data->raycast.alpha - data->player.pov;
    correct_dist *= (cos(data->raycast.beta));
    return(correct_dist);
}
int add_params(t_data *data)
{
    if (data->key.arrow_left == TRUE)
    {
        data->player.pov += 0.1;
    }
    if (data->key.arrow_right == TRUE)
    {
        data->player.pov -= 0.1;
    }
    if (data->key.arrow_up == TRUE)
    {
		move_up(data);
    }
    if (data->key.arrow_down == TRUE)
    {
		move_down(data);
    }
    return (0);
}

int scan(t_data *data)
{
    add_params(data);
    data->raycast.column = data->screen.size.x;
    data->raycast.alpha = data->player.pov - (data->player.fov / 2); // REVIEW optimiser
    if(data->image.img)
		mlx_destroy_image(data->mlx.ptr, data->image.img);
	if (!(data->image.img = mlx_new_image(data->mlx.ptr, data->screen.size.x, data->screen.size.y)))
		return (-1);
	data->image.add_image = mlx_get_data_addr(data->image.img, &data->image.bpp, &data->image.size_line, &data->image.endian); // explication
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
    return (1);
}