/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_geometrical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:20:46 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:26:29 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_rect(t_image *image, t_coord pos, t_coord size, int colors)
{
	t_coord tmp;

	tmp.y = 0;
	while (tmp.y < size.y)
	{
		tmp.x = 0;
		while (tmp.x < size.x)
		{
			*(int*)(image->add_image + (tmp.x + pos.x) * sizeof(int) +
				((tmp.y + pos.y) * image->size_line)) = colors;
			tmp.x++;
		}
		tmp.y++;
	}
}

void	mlx_line(t_data *data, t_coord start, t_coord end, int colors)
{
	t_coord	d;
	t_coord draw;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	draw.x = start.x;
	while (draw.x < end.x)
	{
		draw.y = start.y + d.y * (draw.x - start.x) / d.x;
		mlx_pixel_put(data->mlx.ptr, data->mlx.win, draw.x, draw.y, colors);
		draw.x++;
	}
}

void	mlx_text(t_data *data, t_coord pos, char *text, int colors)
{
	mlx_string_put(data->mlx.ptr, data->mlx.win, pos.x, pos.y, colors, text);
}
