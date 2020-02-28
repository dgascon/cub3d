/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:37:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/28 16:16:36 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RATIO 0.5f

static void	render_mmap(t_data *data, t_coord *pos, t_coord smap, t_coord sbox)
{
	char	current_block;

	while ((*pos).y < smap.y)
	{
		(*pos).x = 0;
		while ((*pos).x < smap.x)
		{
			current_block =
				data->world.map[(*pos).y / sbox.y][(*pos).x / sbox.x];
			if (current_block == '1')
				mlx_rect(&data->minimap, (*pos), sbox, rgb_int(0, 100, 100, 100));
			else if (current_block >= '2')
				mlx_rect(&data->minimap, (*pos), sbox, rgb_int(0, 180, 100, 100));
			else
				mlx_rect(&data->minimap, (*pos), sbox, rgb_int(0, 135, 135, 135));
			(*pos).x += sbox.x;
		}
		(*pos).y += sbox.y;
	}
}

void		minimap(t_data *data)
{
	t_coord pos;
	t_coord	smap;
	t_coord sbox;

	pos = (t_coord) {0, 0};
	sbox.x = ((float)64 * ((float)16 / data->world.size.x)) * RATIO;
	sbox.y = ((float)64 * ((float)8 / data->world.size.y)) * RATIO;
	smap.x = (data->world.size.x * sbox.x);
	smap.y = (data->world.size.y * sbox.y);
	if (!(data->minimap.img = mlx_new_image(data->mlx.ptr, smap.x, smap.y)))
		printf("BITCH\n");
	if (!(data->minimap.add_image = mlx_get_data_addr(data->minimap.img,
		&data->minimap.bpp, &data->minimap.size_line, &data->minimap.endian)))
		printf("BITCH 2\n");
	mlx_rect(&data->minimap, (t_coord) {0, 0}, smap, rgb_int(0, 255, 255, 255));
	render_mmap(data, &pos, smap, sbox);
	mlx_rect(&data->minimap, (t_coord) {data->player.pos.x /
	((float)(data->world.size.x * BLOCK_SIZE) / (float)smap.x),
	data->player.pos.y / ((float)(data->world.size.y * BLOCK_SIZE)
	/ (float)smap.y)}, (t_coord) {5, 5}, rgb_int(0, 255, 105, 180));
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->minimap.img,
			10, 10);
}
