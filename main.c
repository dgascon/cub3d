/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:47:53 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 14:51:13 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <Tk/X11/x.h>

int    key_press(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx.ptr, data->mlx.win);
		exit(1);
	}
	if (key == ARROW_LEFT || key == A) 
		data->player.pov += 0.1;
	else if (key == ARROW_RIGHT || key == D)
		data->player.pov -= 0.1;
	else if (key == ARROW_UP)
		move_up(data);
	else if (key == ARROW_DOWN)
		move_down(data);
	else if (key == Q)
		(data->player.speed < 20) ? data->player.speed += 1 : 0;
	else if (key == Z)
		(data->player.speed > 2) ? data->player.speed -= 1 : 0;
	scan(data);
	return (0);
}


int main(int ac, char **av)
{
	t_data data;

	(void)av;
	if (ac <= 1)
	{
		printf("Map manquante !");
		return (EXIT_FAILURE);
	} 
	data.world.map = parsefile(&data, av[1]);
	if (!(data.mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if ((data.mlx.win = mlx_new_window(data.mlx.ptr, data.screen.size.x,
						data.screen.size.y, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	data.player = (t_player){.fov = M_PI / 3, .pov = M_PI_2, .height_cam = 32,
	.pos.x = 64 * 2.5, .pos.y = 64 * 3.5, .speed = 10};
	data.raycast = (t_raycast) {.alpha = M_PI / 3};
	data.image = (t_image) {.bpp = 32,
	.size_line = data.image.bpp * data.screen.size.x, .endian = 0};
	data.tex = (t_image) {.bpp = 32,
	.size_line = data.tex.bpp * 64, .endian = 0};
	scan(&data);
	mlx_hook(data.mlx.win, KeyPress, NoEventMask, key_press, &data);
	mlx_loop(data.mlx.ptr);
	return (EXIT_SUCCESS);
}