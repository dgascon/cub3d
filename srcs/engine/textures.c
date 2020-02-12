/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/12 12:34:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 13:14:41 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int	init_texture(t_data *data, t_image *image, char *path)
{
	if (!(image->img = mlx_xpm_file_to_image(data->mlx.ptr, path,
			&image->size.x, &image->size.y)))
	{
		ft_printf("Erreur : image non existante conversion impossible.\n");
		return (EXIT_FAILURE);
	}
	if (!(image->add_image = mlx_get_data_addr(image->img,
			&image->bpp, &image->size_line, &image->endian)))
	{
		ft_printf("Erreur : récupération de l'adresse de l'image.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("[INFO] Chargement de '%s'.\n", path);
	return (EXIT_SUCCESS);
}