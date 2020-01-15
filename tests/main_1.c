/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_1.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/26 18:55:32 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 00:14:58 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int main(int ac, char **av)
{
    t_data		data;
	t_world		world;
	t_raycast	raycast;
		
	(void)av;
	if (ac <= 1)
	{
		ft_printf("world manquante !");
		return (0);
	}
	if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
	data.width = 320;
	data.height = 200;
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, data.width, data.height, "Hello world")) == NULL)
        return (EXIT_FAILURE);
	if (!(init_world(&world)))
		return (EXIT_FAILURE);
	if (TRUE && !(show_2d_world(&world)))
		return (EXIT_FAILURE);
	world.player = (t_player){.fov = M_PI / 3, .pov = M_PI_2, .height = 32,
								.coord.x = 64 * 2 + 32, .coord.y = 64 * 2 + 32};
	raycast = (t_raycast) {.alpha = M_PI_2 - (M_PI / 6), .column = data.width};
	int x = data.width;
	while (x--)
	{
		raycast.dist = shortest_dist(linear_intersec_h(&world, &raycast), linear_intersec_v(&world, &raycast));
		printf("Calc : %5f\n", world.player.fov / data.width);
		raycast.alpha += (world.player.fov / data.width);
		printf("Alpha : %5f\n", raycast.alpha);
		if (raycast.alpha > 2 * M_PI)
			raycast.alpha = 0;
	}
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}