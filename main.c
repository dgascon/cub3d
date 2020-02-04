/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:47:53 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:47:14 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <Tk/X11/x.h>

int init_texture(t_data* data)
{
	if (!(data->Wtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/wood.xpm", &data->Wtex.size, &data->Wtex.size)))
		return (printf("erreur1"));
	if (!(data->Wtex.add_image = mlx_get_data_addr(data->Wtex.img, &data->Wtex.bpp, &data->Wtex.size_line, &data->Wtex.endian)))
		return (printf("erreur2"));
	if (!(data->Ftex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/ice.xpm", &data->Ftex.size, &data->Ftex.size)))
		return (printf("erreur1"));
	if (!(data->Ftex.add_image = mlx_get_data_addr(data->Ftex.img, &data->Ftex.bpp, &data->Ftex.size_line, &data->Ftex.endian)))
		return (printf("erreur2"));
	if (!(data->Rtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/vitrail-3.xpm", &data->Rtex.size, &data->Rtex.size)))
		return (printf("erreur1"));
	if (!(data->Rtex.add_image = mlx_get_data_addr(data->Rtex.img, &data->Rtex.bpp, &data->Rtex.size_line, &data->Rtex.endian)))
		return (printf("erreur2"));
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
	data.player = (t_player){.fov = M_PI /3, .height_cam = 32, .speed = 10};
	if (parsefile(&data, av[1]) <= 0)
		return (EXIT_FAILURE);
	if (!(data.mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if ((data.mlx.win = mlx_new_window(data.mlx.ptr, data.screen.size.x,
						data.screen.size.y, "Dgascon && Nlecaill")) == NULL)
		return (EXIT_FAILURE);
	
	data.raycast = (t_raycast) {.alpha = M_PI / 3, .delta_ang = (data.player.fov / data.screen.size.x)};
	data.image = (t_image) {.bpp = 32,
	.size_line = data.image.bpp * data.screen.size.x, .endian = 0};
	data.player.dist_proj_plane = ((double)(data.screen.size.x) / 2) / tan(data.player.fov / 2);
	data.player.CST = (BLOCK_SIZE * data.player.dist_proj_plane) ;
	data.player.hdv = data.screen.size.y / 2;
	data.key = (t_key){.arrow_left = FALSE, .arrow_right = FALSE, .arrow_up = FALSE, .arrow_down = FALSE,
	 .incspeed = FALSE, .decspeed = FALSE, .D = FALSE, .A = FALSE, .S = FALSE, .W = FALSE};
	data.pi = (t_pi){.dPI = 2 * M_PI, .tPId = 3*M_PI/2};
	if (init_texture(&data) != 0)
		return (EXIT_FAILURE);
	if (!(data.image.img = mlx_new_image(data.mlx.ptr, data.screen.size.x, data.screen.size.y)))
		return (EXIT_FAILURE);

	if (!(data.image.add_image = mlx_get_data_addr(data.image.img, &data.image.bpp, &data.image.size_line, &data.image.endian)))
		return (EXIT_FAILURE);
	mlx_loop_hook(data.mlx.ptr, scan, &data);
	mlx_hook(data.mlx.win, KeyPress, NoEventMask, key_press, &data);
	mlx_hook(data.mlx.win, KeyRelease, NoEventMask, key_release, &data);
	mlx_hook(data.mlx.win, DestroyNotify, NoEventMask, destroy, &data);
	mlx_loop(data.mlx.ptr);
	return (EXIT_SUCCESS);
}