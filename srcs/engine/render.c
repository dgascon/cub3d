/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:44:35 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/05 19:00:03 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		select_wall_color(t_data *data, float prptn, int wall_row,
								int dir)
{
	t_coord	ratio;
	float	proportion;

	proportion = (float)data->w_tex[dir].size.x / BLOCK_SIZE;
	ratio.y = (int)(prptn * wall_row) % data->w_tex[dir].size.y;
	if (data->raycast.face_detect == 'V')
	{
		ratio.x = (int)(data->raycast.inter.y * proportion)
			% data->w_tex[dir].size.x;
	}
	else
	{
		ratio.x = (int)(data->raycast.inter.x * proportion)
			% data->w_tex[dir].size.x;
	}
	if (dir == 2 || dir == 3)
		ratio.x = data->w_tex[dir].size.x - (ratio.x + 1);
	return (darken_wall(data->raycast.dist, *(int*)(data->w_tex[dir].add_image
	+ (data->w_tex[dir].size_line * ratio.y) + (ratio.x * sizeof(int)))));
}

static	int		draw_wall(t_data *data, int height_proj_plane,
					int qte_mur_sous_hdv, int direction)
{
	int		row;
	float	racourcis;
	int		wall_row;
	char	*add_opp;
	int		h_max;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	wall_row = 0;
	row = data->player.hdv - (height_proj_plane - qte_mur_sous_hdv);
	if (row < 0)
	{
		wall_row = 0 - row;
		row = 0;
	}
	racourcis = (float)data->w_tex[direction].size.y / height_proj_plane;
	if (!data->screen.ceil_tex || !data->screen.floor_tex)
		fill_background(data);
	h_max = data->player.hdv + qte_mur_sous_hdv;
	if (h_max > data->screen.size.y - 1)
		h_max = data->screen.size.y - 1;
	while (row < h_max)
		*(int*)(add_opp + (row++ * data->image.size_line)) =
			select_wall_color(data, racourcis, wall_row++, direction);
	return (h_max);
}

int				fill_column(t_data *data, int direction)
{
	int		height_proj_plane;
	int		qte_mur_sous_hdv;
	int		h_max;

	height_proj_plane = (float)data->player.cst / data->raycast.dist;
	qte_mur_sous_hdv = (float)height_proj_plane /
					((float)BLOCK_SIZE / data->player.height_cam);
	h_max = draw_wall(data, height_proj_plane, qte_mur_sous_hdv, direction);
	if (data->screen.ceil_tex && data->screen.floor_tex)
		pt_floor_ceil(data, h_max - 1, qte_mur_sous_hdv, height_proj_plane);
	print_sprite(data);
	return (0);
}
