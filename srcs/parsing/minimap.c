/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:37:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:51:54 by dgascon          ###   ########lyon.fr   */
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
			rgb = 0;
			block = data->world.map[pos.y][pos.x];
			if (block == '1')
				rgb = rgb_int(0, 100, 100, 100);
			else if (block >= '2' && block <= '9')
				rgb = rgb_int(0, 180, 100, 100);
			else if (ft_charstr(block, "NWES0"))
				rgb = rgb_int(0, 135, 135, 135);
			if (rgb != 0)
				mlx_rect(&data->image, (t_coord) {.y = (scale.y * pos.y),
					.x = scale.x * pos.x}, scale, rgb);
			pos.x++;
		}
		pos.y++;
	}
}

int			minimap(t_data *data)
{
	t_coord scale;

	scale.y = data->screen.size.y / (BLOCK_SIZE + data->world.size.y);
	scale.x = data->screen.size.x / (BLOCK_SIZE + data->world.size.x);
	render_mmap(data, scale);
	mlx_rect(&data->image, (t_coord){.y = (int)(data->player.pos.y /
		BLOCK_SIZE) * scale.y, .x = (int)(data->player.pos.x /
		BLOCK_SIZE) * scale.x}, scale, rgb_int(0, 255, 105, 180));
	return (EXIT_SUCCESS);
}
