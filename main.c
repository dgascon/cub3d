/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:47:53 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 16:14:06 by dgascon     ###    #+. /#+    ###.fr     */
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
	if (key == ARROW_LEFT)
	{
		data->key.arrow_left = TRUE;
	}
	else if (key == ARROW_RIGHT)
	{
		data->key.arrow_right = TRUE;
	}	
	else if (key == ARROW_UP)
	{
		data->key.arrow_up = TRUE;
	}
	else if (key == ARROW_DOWN)
	{
		data->key.arrow_down = TRUE;
	}
	else if (key == Q)
		(data->player.speed < 20) ? data->player.speed += 1 : 0;
	else if (key == Z)
		(data->player.speed > 2) ? data->player.speed -= 1 : 0;
	else if (key == D)
		data->player.pos.x +=5;
	else if (key == A)
		data->player.pos.x -= 5;
	else if (key == W)
		data->player.pos.y -= 5;
	else if (key == S)
		data->player.pos.y +=5;
	return (0);
}

int    key_release(int key, t_data *data)
{
	if (key == ARROW_LEFT)
	{
		data->key.arrow_left = FALSE;
	}
	if (key == ARROW_RIGHT)
	{
		data->key.arrow_right = FALSE;
	}if (key == ARROW_UP)
	{
		data->key.arrow_up = FALSE;
	}if (key == ARROW_DOWN)
	{
		data->key.arrow_down = FALSE;
	}
	return (0);
}

int init_texture(t_data* data)
{
	data->Wtex = (t_image) {.bpp = 32,
	.size_line = data->Wtex.bpp * BLOCK_SIZE, .endian = 0};
	if (!(data->Wtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/bricks64.xpm", &data->Wtex.size, &data->Wtex.size)))
		return (printf("erreur1"));
	if (!(data->Wtex.add_image = mlx_get_data_addr(data->Wtex.img, &data->Wtex.bpp, &data->Wtex.size_line, &data->Wtex.endian)))
		return (printf("erreur2"));
	data->Ftex = (t_image) {.bpp = 32,
	.size_line = data->Ftex.bpp * BLOCK_SIZE, .endian = 0};
	if (!(data->Ftex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/ice.xpm", &data->Ftex.size, &data->Ftex.size)))
		return (printf("erreur1"));
	if (!(data->Ftex.add_image = mlx_get_data_addr(data->Ftex.img, &data->Ftex.bpp, &data->Ftex.size_line, &data->Ftex.endian)))
		return (printf("erreur2"));
	data->Rtex = (t_image) {.bpp = 32,
	.size_line = data->Rtex.bpp * BLOCK_SIZE, .endian = 0};
	if (!(data->Rtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/vitrail-3.xpm", &data->Rtex.size, &data->Rtex.size)))
		return (printf("erreur1"));
	if (!(data->Rtex.add_image = mlx_get_data_addr(data->Rtex.img, &data->Rtex.bpp, &data->Rtex.size_line, &data->Rtex.endian)))
		return (printf("erreur2"));
	data->Vtex = (t_image) {.bpp = 32,
	.size_line = data->Vtex.bpp * 24, .endian = 0};
	if (!(data->Vtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/viseur.xpm", &data->Vtex.size, &data->Vtex.size)))
		return (printf("erreur1"));
	if (!(data->Vtex.add_image = mlx_get_data_addr(data->Vtex.img, &data->Vtex.bpp, &data->Vtex.size_line, &data->Vtex.endian)))
		return (printf("erreur2"));
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
						data.screen.size.y, "Dgascon && Nlecaill")) == NULL)
		return (EXIT_FAILURE);
	data.player = (t_player){.fov = M_PI /3 , .pov = 2*M_PI, .height_cam = 32,
	.pos.x = 64 * 2.5, .pos.y = 64 * 3.5, .speed = 10};
	data.raycast = (t_raycast) {.alpha = M_PI / 3, .delta_ang = (data.player.fov / data.screen.size.x)};
	data.image = (t_image) {.bpp = 32,
	.size_line = data.image.bpp * data.screen.size.x, .endian = 0};
	data.player.dist_proj_plane = ((double)(data.screen.size.x) / 2) / tan(data.player.fov / 2);
	if (init_texture(&data) != 0)
		return (EXIT_FAILURE);
	if (!(data.image.img = mlx_new_image(data.mlx.ptr, data.screen.size.x, data.screen.size.y)))
		return (EXIT_FAILURE);
	mlx_loop_hook(data.mlx.ptr, scan, &data);
	mlx_hook(data.mlx.win, KeyPress, NoEventMask, key_press, &data);
	mlx_hook(data.mlx.win, KeyRelease, NoEventMask, key_release, &data);
	mlx_loop(data.mlx.ptr);
	return (EXIT_SUCCESS);
}