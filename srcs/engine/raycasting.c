/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:37:04 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:24:16 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

double short_dist(t_data *data)
{
    double  dist_h;
    double  dist_v;
    double  correct_dist;
    
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
    correct_dist *= (cos(data->raycast.beta));
    return(correct_dist);
}
int add_params(t_data *data)
{
    if (data->key.arrow_left == TRUE)
    {
        data->player.pov += 0.1;
		if (data->player.pov > data->pi.dPI)
        {
            data->player.pov -= data->pi.dPI;
        }
    }
    if (data->key.arrow_right == TRUE)
    {
        data->player.pov -= 0.1;
        if (data->player.pov < 0)
            data->player.pov += data->pi.dPI;
    }
    if (data->key.arrow_up == TRUE)
    {
        data->player.hdv -= 25;//(double)data->screen.size.y / 100;

    }
    if (data->key.W == TRUE)
    {
		move_up(data, data->player.pov);
    }
    if (data->key.arrow_down == TRUE)
    {
        data->player.hdv += 25;//(double)data->screen.size.y / 100;
    }
    if (data->key.S == TRUE)
    {
		move_down(data, data->player.pov);
    }
    if (data->key.A == TRUE)
    {
        {
         //   data->player.hdv += 25;
        }
       move_up(data, data->player.pov + M_PI_2);
    }
    if (data->key.D == TRUE)
    {
        if (data->player.height_cam > 5)
        {
           // data->player.hdv -= 25;
        }
        move_up(data, data->player.pov - M_PI_2);
    }
    if (data->key.incspeed)
    	(data->player.speed < 20) ? data->player.speed += 1 : 0;
    if (data->key.decspeed)
		(data->player.speed > 2) ? data->player.speed -= 1 : 0;
    if (data->key.JUMP)
    {
        if (data->player.height_cam < 48)
            data->player.height_cam += 5;
    }
    else if (data->key.SQUAT)
    {
        if (data->player.height_cam > 16)
            data->player.height_cam -= 5;
    }
    else
    {
        if (data->player.height_cam > 32)
            data->player.height_cam -= 5;
        else if (data->player.height_cam < 32)
            data->player.height_cam +=5;
    }
    return (0);
}

int scan(t_data *data)
{
    add_params(data);
    mlx_clear_window(data->mlx.ptr, data->mlx.win);
    data->raycast.column = data->screen.size.x;
    data->raycast.alpha = data->player.pov - (data->player.fov / 2); // REVIEW optimiser
    while (data->raycast.column >= 0)
	{
		data->raycast.alpha += data->raycast.delta_ang; // REVIEW optimiser
		if (data->raycast.alpha >= data->pi.dPI) // REVIEW optimiser
			data->raycast.alpha -= data->pi.dPI; // REVIEW optimiser
		if (data->raycast.alpha < 0)
			data->raycast.alpha += data->pi.dPI; // REVIEW optimiser
		data->raycast.dist = short_dist(data);
		fill_column(data);
        data->raycast.column--;
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->image.img, 0, 0);
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->Vtex.img, data->screen.size.x / 2 - 12, data->screen.size.y / 2 - 12);
    return (1);
}