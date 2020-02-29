/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 04:37:46 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:26:56 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_data *data)
{
	int i;

	i = -1;
	while (++i < HUD_TEX)
	{
		if (data->hud_tex[i].img)
			mlx_destroy_image(data->mlx.ptr, data->hud_tex[i].img);
	}
	i = -1;
	while (++i < OBJ_TEX)
	{
		if (data->object[i].img && data->object[i].valid)
		{
			mlx_destroy_image(data->mlx.ptr, data->object[i].img);
		}
	}
	i = -1;
	while (++i < W_TEX)
		if (data->w_tex[i].img && data->w_tex[i].valid)
			mlx_destroy_image(data->mlx.ptr, data->w_tex[i].img);
	
	if (data->image.img)
	{
		mlx_destroy_image(data->mlx.ptr, data->image.img);
		mlx_destroy_window(data->mlx.ptr, data->mlx.win);
	}
	wrdestroy();
	exit(0);
	return (EXIT_FAILURE);
}
