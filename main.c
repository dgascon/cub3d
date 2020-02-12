/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:47:53 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 15:35:27 by nlecaill    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <Tk/X11/x.h>

int		init_window(t_data *data)
{
	if (!(data->mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if ((data->mlx.win = mlx_new_window(data->mlx.ptr, data->screen.size.x,
			data->screen.size.y, "Dgascon && Nlecaill")) == NULL)
		return (EXIT_FAILURE);
	if (!(data->image.img = mlx_new_image(data->mlx.ptr, data->screen.size.x,
			data->screen.size.y)))
		return (EXIT_FAILURE);
	if (!(data->image.add_image = mlx_get_data_addr(data->image.img,
			&data->image.bpp, &data->image.size_line, &data->image.endian)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


//DONE collision avec les sprites
//DONE parsing: ajouter automatiquement les sprites a la liste chaine
//DONE parsing: rendre les valeurs dependante de la BLOCK_SIZE
//DONE gerer le beugue d'affichage des sprites
//DONE regler le probleme de speed quand on court
//DONE rendre la vitesse dependante de la taille de la map
//DONE ralentir la monter et la descente du saut
//DONE gerer le plafond et le avec une block_size differente
//DONE gerer les sprites avec block_size different
//DONE tableau de texture 
//TODO Ajouter une regle makefile debug
//TODO Corriger la direction de mouvement
//TODO Si la taille de fenêtre demandée dans la map est plus grande que celle de l’écran, la taille de fenêtre doit être celle de l’écran
//TODO rendre la minimap sans relation avec la blocksize

int main(int ac, char **av)
{
	t_data data;

	(void)av;
	if (ac <= 1)
	{
		ft_printf("Map manquante !");
		return (EXIT_FAILURE);
	} 
	data.lst = NULL;
	data.player = (t_player){.fov = M_PI /3, .height_cam = BLOCK_SIZE/2, .speed = MAX_SPEED/2};
	if (parsefile(&data, av[1]) <= 0)
		return (EXIT_FAILURE);
	data.raycast = (t_raycast) {.alpha = M_PI / 3, .delta_ang = (data.player.fov / data.screen.size.x)};
	// data.image = (t_image) {.bpp = 32,
	// .size_line = data.image.bpp * data.screen.size.x, .endian = 0};
	data.player.dist_proj_plane = ((float)data.screen.size.x / 2) / tan(data.player.fov / 2);
	data.player.cst = (BLOCK_SIZE * data.player.dist_proj_plane);
	data.player.hdv = data.screen.size.y / 2;
	data.actions = (t_actions){};
	data.world.locked = 1;
	data.world.was_lock = 1;
	mlx_loop_hook(data.mlx.ptr, scan, &data);
	mlx_hook(data.mlx.win, KeyPress, NoEventMask, key_press, &data);
	mlx_hook(data.mlx.win, KeyRelease, NoEventMask, key_release, &data);
	mlx_hook(data.mlx.win, DestroyNotify, NoEventMask, destroy, &data);
	mlx_loop(data.mlx.ptr);
	return (EXIT_SUCCESS);
}