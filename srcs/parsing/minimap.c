/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minimap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 19:37:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 17:42:00 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

#define RATIO 0.5f

void	minimap(t_data *data)
{
	t_coord pos;
	t_coord	sizemap;
	t_coord sizebox;
	char current_block;

	pos = (t_coord) {};
	sizebox.x = ((float)64 * ((float)16 / data->world.size.x)) * RATIO;
	sizebox.y = ((float)64 * ((float)8 / data->world.size.y)) * RATIO;
	sizemap.x = (data->world.size.x * sizebox.x);
	sizemap.y = (data->world.size.y * sizebox.y);
	if (!(data->minimap.img = mlx_new_image(data->mlx.ptr, sizemap.x, sizemap.y)))
		printf("BITCH\n");
	if (!(data->minimap.add_image = mlx_get_data_addr(data->minimap.img, &data->minimap.bpp, &data->minimap.size_line, &data->minimap.endian)))
		printf("BITCH 2\n");
	mlx_rect(&data->minimap, (t_coord) {}, sizemap, rgb_int(255, 255, 255));
	while (pos.y < sizemap.y)
	{
		pos.x = 0;
		while (pos.x < sizemap.x)
		{
			current_block = data->world.map[pos.y / sizebox.y][pos.x / sizebox.x];
			if (current_block == '1' || current_block == '2')
				mlx_rect(&data->minimap, pos, sizebox, rgb_int(100, 100, 100));
			else if (current_block > '2')
				mlx_rect(&data->minimap, pos, sizebox, rgb_int(180, 100, 100));
			else
				mlx_rect(&data->minimap, pos, sizebox, rgb_int(135, 135, 135));
			pos.x += sizebox.x;
		}
		pos.y += sizebox.y;
	}
	mlx_rect(&data->minimap, (t_coord) {data->player.pos.x / ((float)(data->world.size.x * BLOCK_SIZE) / (float)sizemap.x), data->player.pos.y / ((float)(data->world.size.y * BLOCK_SIZE) / (float)sizemap.y)}, (t_coord) {5, 5}, rgb_int(255, 105, 180));	
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->minimap.img, 10, 10);
}