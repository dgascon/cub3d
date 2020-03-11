/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:37:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/11 17:53:41 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_mmap(t_data *data, t_coord scale)
{
	t_coord	pos;
	char	block;
	int		rgb;

	pos = (t_coord) {0, 0};
	while (pos.y < data->world.size.y)
	{
		pos.x = 0;
		while (data->world.map[pos.y][pos.x])
		{
			block = data->world.map[pos.y][pos.x];
			if (block == '1')
				rgb = rgb_int(0, 100, 100, 100);
			else if (block >= '2' && block <= '9')
				rgb = rgb_int(0, 180, 100, 100);
			else if (ft_charstr(block, "NWES0"))
				rgb = rgb_int(0, 135, 135, 135);
			else
				rgb = rgb_int(255, 0, 0, 0);
			mlx_rect(&data->minimap, (t_coord) {.y = (scale.y * pos.y),
				.x = scale.x * pos.x}, scale, rgb);
			pos.x++;
		}
		pos.y++;
	}
}

int			minimap(t_data *data)
{
	t_coord scale;
	t_coord smap;

	scale.y = data->screen.size.y / (BLOCK_SIZE + data->world.size.y);
	scale.x = data->screen.size.x / (BLOCK_SIZE + data->world.size.x);
	smap.x = data->world.size.x * scale.x;
	smap.y = data->world.size.y * scale.y;
	if (!data->minimap.img)
	{
		if (!(data->minimap.img = mlx_new_image(data->mlx.ptr, smap.x, smap.y)))
			return (ft_msg(TM_ERROR, "MLX", 1, RED));
		if (!(data->minimap.add_image = mlx_get_data_addr(data->minimap.img,
		&data->minimap.bpp, &data->minimap.size_line, &data->minimap.endian)))
			return (ft_msg(TM_ERROR, "Recover image", 1, RED));
	}
	mlx_rect(&data->minimap, (t_coord) {0, 0}, smap, rgb_int(255, 255,
		255, 255));
	render_mmap(data, scale);
	mlx_rect(&data->minimap, (t_coord) {.y = (data->player.pos.y / BLOCK_SIZE) *
	scale.y, .x = (data->player.pos.x / BLOCK_SIZE) * scale.x}, scale,
	rgb_int(0, 255, 105, 180));
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->minimap.img, 10,
		10);
	return (EXIT_SUCCESS);
}
