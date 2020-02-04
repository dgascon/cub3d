/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minimap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 19:37:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 20:05:19 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(t_data *data, int width, int height)
{
	t_coord pos;
	t_coord	size;
	t_coord offset;

	offset = (t_coord) {.x = 1, .y = 1};
	pos = (t_coord) {.y = offset.y};
	size = (t_coord) {width, height};

	mlx_rect(data, (t_coord) {offset.x - 1, offset.y - 1}, (t_coord) {data->world.size.x * BLOCK_SIZE + (data->world.size.x + 1), (data->world.size.y) * BLOCK_SIZE + data->world.size.y + 1}, rgb_int(255, 255, 255));
	while (pos.y < data->world.size.y * BLOCK_SIZE)
	{
		pos.x = offset.x;
		while (pos.x < data->world.size.x * BLOCK_SIZE)
		{
			if (data->world.map[pos.y / BLOCK_SIZE][pos.x / BLOCK_SIZE] == '1')
				mlx_rect(data, pos, size, rgb_int(100, 100, 100));
			else
				mlx_rect(data, pos, size, rgb_int(135, 135, 135));
			
			mlx_rect(data, (t_coord) {data->player.pos.x, data->player.pos.y}, (t_coord) {5, 5}, rgb_int(255, 105, 180));	
			pos.x += size.x + offset.x;
		}
		pos.y += size.y + offset.y;
	}
}