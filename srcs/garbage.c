/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 04:37:46 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:22:26 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	whilefree(int max, t_data *data, t_image *img)
{
	int i;

	i = -1;
	while (++i < max)
	{
		if (img[i].img && img[i].valid)
			mlx_destroy_image(data->mlx.ptr, img[i].img);
	}
}

int			destroy(t_data *data)
{
	whilefree(HUD_TEX, data, data->hud_tex);
	whilefree(OBJ_TEX, data, data->obj_tex);
	whilefree(W_TEX, data, data->w_tex);
	if (data->image.img)
	{
		mlx_destroy_image(data->mlx.ptr, data->image.img);
		mlx_destroy_window(data->mlx.ptr, data->mlx.win);
		free(data->mlx.ptr);
	}
	wrdestroy();
	exit(0);
	return (EXIT_FAILURE);
}
