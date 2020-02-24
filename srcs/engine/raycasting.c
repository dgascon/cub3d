/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:37:04 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:53:56 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		short_dist(t_data *data)
{
	float	dist_h;
	float	dist_v;
	float	correct_dist;

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
	return (correct_dist);
}

void		put_text_to_screen(t_data *data)
{
	static int	timer = -1;
	static int	a = 0;
	char		text[2][50] = {" ", "doors unlocked"};

	if (0 && a == 0)
	{
		a = 1;
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

void		*casting(void *param)
{
	int		direction;
	t_data	*data;

	data = (t_data*)param;
	while (data->raycast.column >= data->raycast.end)
	{
		data->raycast.alpha += data->raycast.delta_ang;
		if (data->raycast.alpha >= _2PI)
			data->raycast.alpha -= _2PI;
		(data->raycast.alpha < 0) ? (data->raycast.alpha += _2PI) : 0;
		data->raycast.dist = short_dist(data);
		if (data->raycast.face_detect == 'H')
		{
			direction = (int)data->raycast.inter.y % BLOCK_SIZE;
			direction = (direction == 0) ? 2 : 0;
		}
		else if (data->raycast.face_detect == 'V')
		{
			direction = (int)data->raycast.inter.x % 64;
			direction = (direction == 0) ? 1 : 3;
		}
		fill_column(data, direction);
		data->raycast.column--;
	}
	if (data->th_num > 0)
		pthread_exit(NULL);
	return(NULL);
}

int			scan(t_data *data)
{
	pthread_t	thread_id[NB_THREAD];
	t_data		th_data[NB_THREAD];
	int			i;

	i = 0;
	actionscontrol(data);
	lsprite_sort(&data->lst);
	data->raycast.alpha = data->player.pov - (data->player.fov / 2);
	while (i < NB_THREAD)
	{
		th_data[i] = *data;
		th_data[i].raycast.column =
			(NB_THREAD - i) * data->screen.size.x / NB_THREAD;
		th_data[i].raycast.alpha =
			data->raycast.alpha + (i * data->player.fov / NB_THREAD);
		th_data[i].raycast.end =
			data->screen.size.x - (i + 1) * data->screen.size.x / NB_THREAD;
		th_data[i].th_num = i;
		i++;
	}
	i = 0;
	while (i < NB_THREAD - 1)
	{
		pthread_create(&thread_id[i], NULL, casting, &th_data[i + 1]);
		i++;
	}
	casting(&th_data[0]);
	while (i > 0)
		pthread_join(thread_id[i-- - 1], NULL);
	if (data->bmp_save)
	{
		save_bmp(data);
		destroy(data);
	}
	mlx_put_image_to_window(data->mlx.ptr,
		data->mlx.win, data->image.img, 0, 0);
	if (data->hud_tex[0].img)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
		data->hud_tex[0].img, data->screen.size.x / 2, data->screen.size.y / 2);
	if (data->player.show_minimap)
		minimap(data);
	put_text_to_screen(data);
	return (1);
}

/**

#include "cub3d.h"

float		short_dist(t_data *data)
{
	float	dist_h;
	float	dist_v;
	float	correct_dist;

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
	return (correct_dist);
}

void		*casting(void *param)
{
	int		direction;
	t_data	*data;

	data = (t_data*)param;
	printf("%d\n", data->th_num);
	while (data->raycast.column >= data->raycast.end)
	{
		data->raycast.alpha += data->raycast.delta_ang;
		(data->raycast.alpha >= _2PI) ? data->raycast.alpha -= _2PI : 0;
		(data->raycast.alpha < 0) ? (data->raycast.alpha += _2PI) : 0;
		data->raycast.dist = short_dist(data);
		if (data->raycast.face_detect == 'H')
		{
			direction = (int)data->raycast.inter.y % BLOCK_SIZE;
			direction = (direction == 0) ? 2 : 0;
		}
		else if (data->raycast.face_detect == 'V')
		{
			direction = (int)data->raycast.inter.x % BLOCK_SIZE;
			direction = (direction == 0) ? 1 : 3;
		}
		fill_column(data, direction);
		data->raycast.column--;
	}
	(data->th_num > 0) ? pthread_exit(NULL) : 0;
	return (NULL);
}

void	init_threads(t_data	th_data[NB_THREAD], t_data *data,
		pthread_t thread_id[NB_THREAD])
{
	int i;

	i = 0;
	while (i < NB_THREAD)
	{
		th_data[i] = *data;
		th_data[i].raycast.column =
			(NB_THREAD - i) * data->screen.size.x / NB_THREAD;
		th_data[i].raycast.alpha =
			data->raycast.alpha + (i * data->player.fov / NB_THREAD);
		th_data[i].raycast.end =
			data->screen.size.x - (i + 1) * data->screen.size.x / NB_THREAD;
		th_data[i].th_num = i;
		i++;
	}
	i = 0;
	while (i < NB_THREAD - 1)
	{
		pthread_create(&thread_id[i], NULL, casting, &th_data[i + 1]);
		i++;
	}
}

int			scan(t_data *data)
{
	pthread_t	thread_id[NB_THREAD];
	t_data		th_data[NB_THREAD];
	int			i;

	i = 0;
	actionscontrol(data);
	lsprite_sort(&data->lst);
	data->raycast.alpha = data->player.pov - (data->player.fov / 2);
	init_threads(th_data, data, thread_id);
	casting(&th_data[0]);
	while (i > 0)
		pthread_join(thread_id[i-- - 1], NULL);
	if (data->bmp_save)
	{
		save_bmp(data);
		destroy(data);
	}
	mlx_put_image_to_window(data->mlx.ptr,
		data->mlx.win, data->image.img, 0, 0);	
	if (data->hud_tex[0].img)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
		data->hud_tex[0].img, data->screen.size.x / 2, data->screen.size.y / 2);
	(data->player.show_minimap) ? minimap(data) : 0;
	return (1);
}
*/