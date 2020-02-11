/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   object.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/11 15:10:08 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:25:15 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int	init_object(t_data *data, char *path, int id)
{
	t_image *current_tex;

	current_tex = &data->object[id - 3];
	if (!(current_tex->img = mlx_xpm_file_to_image(data->mlx.ptr, path,
            &current_tex->sizex, &current_tex->sizey)))
		return (EXIT_FAILURE);
	if (!(current_tex->add_image = mlx_get_data_addr(current_tex->img,
            &current_tex->bpp, &current_tex->size_line, &current_tex->endian)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}