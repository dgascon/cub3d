/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:30:11 by nlecaill          #+#    #+#             */
/*   Updated: 2020/05/05 18:59:01 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		select_sprite_color(t_f_coord offset, int wall_row,
				t_image sprite, t_f_coord lim)
{
	t_coord ratio;

	ratio.y = (int)(((float)sprite.size.y / lim.y)
			* wall_row) % sprite.size.y;
	ratio.x = (int)(((float)sprite.size.x / lim.x)
			* (lim.x / 2 - offset.x)) % sprite.size.x;
	return (*(int*)(sprite.add_image
	+ (sprite.size_line * ratio.y) + (ratio.x * sizeof(int))));
}

static void		print_sprite2(t_data *data, t_f_coord lim, t_f_coord offset,
								t_lsprite *list)
{
	int				row;
	unsigned int	val;
	int				cmp;
	unsigned int	tmp;

	cmp = 0;
	if (offset.x < lim.x / 2
		&& (list->dist * cosf(data->raycast.beta)) < data->raycast.dist
		&& offset.x > -(lim.x / 2))
	{
		lim.y = (BLOCK_SIZE / 2) * (data->player.dist_proj_plane / list->dist);
		row = data->player.hdv +
			((data->player.height_cam - BLOCK_SIZE / 2)
			/ list->dist) * data->player.dist_proj_plane;
		while (cmp < lim.y && row < data->screen.size.y - 1)
		{
			tmp = select_sprite_color(offset, cmp, list->texture, lim);
			val = darken_wall(list->dist, tmp);
			if (tmp != 0x00000000 && row > 0)
				*(int*)(data->image.add_image + (row * data->image.size_line) +
				data->raycast.column * sizeof(int)) = val;
			row++;
			cmp++;
		}
	}
}

void			print_sprite(t_data *data)
{
	t_f_coord		lim;
	t_f_coord		offset_mid_object;
	float			angle_raycast_mid_obj;
	t_lsprite		*list;

	list = data->lst;
	while (list != NULL)
	{
		if (list->visible[data->th_num] == 1)
		{
			angle_raycast_mid_obj = data->raycast.alpha -
				((M_PI_2 - atanf((float)(list->pos.y - data->player.pos.y)
				/ (list->pos.x - data->player.pos.x))) + M_PI_2);
			offset_mid_object.x = tanf(angle_raycast_mid_obj) * list->dist;
			offset_mid_object.x *= (data->player.dist_proj_plane / list->dist);
			lim.x = (BLOCK_SIZE / 2) *
					(data->player.dist_proj_plane / list->dist);
			print_sprite2(data, lim, offset_mid_object, list);
			list->visible[data->th_num] = 0;
		}
		list = list->next;
	}
}
