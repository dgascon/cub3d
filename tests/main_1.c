/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_1.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/26 18:55:32 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 23:02:38 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int main(int ac, char **av)
{
    t_data		data;
		
	(void)av;
	if (ac <= 1)
	{
		ft_printf("world manquante !");
		return (0);
	}
	if ((data.mlx.ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
	data.window.width = 320;
	data.window.height = 200;
    if ((data.mlx.win = mlx_new_window(data.mlx.ptr, data.window.width, data.window.height, "Hello world")) == NULL)
        return (EXIT_FAILURE);
	init_world(&data);
	int x = 0;
	int y = 0;
	while (y <= 5)
	{
		x = 0;
		while (x <= 5)
		{
			if (data.world.map[x][y] != 0)
				printf("[%c]", data.world.map[x][y]);
			x++;
		}
		printf("\n");
		y++;
	}
	data.world.player = (t_player){.fov = M_PI / 3, .pov = M_PI_2, .height = 32, .pos.x = 64 * 2 + 32, .pos.y = 64 * 3 + 32};
	data.world.player.ray = (t_raycast) {.alpha = M_PI / 3, .column = data.window.width};
	
	while (data.world.player.ray.column--)
	{
		data.world.player.ray.dist = shortest_dist(&data, linear_intersec_h(&data), linear_intersec_v(&data));
	 	data.world.player.ray.alpha += (data.world.player.fov / data.window.width);
		if (data.world.player.ray.alpha > 2 * M_PI)
			data.world.player.ray.alpha -= 2 * M_PI;
		put_column(&data);
	}
    mlx_loop(data.mlx.ptr);
    return (EXIT_SUCCESS);
}