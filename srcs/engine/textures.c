/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:34:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 12:30:22 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_texture(t_data *data, t_image *image, char *path)
{
	char *tmp;
	
	if (!(image->img = mlx_xpm_file_to_image(data->mlx.ptr, path,
			&image->size.x, &image->size.y)))
	{
		tmp = ft_strmjoin("sss", "Texture not found. ('", path, "').");
		ft_msg(TM_ERROR, tmp, 1, RED);
		wrfree(tmp);
		return (EXIT_FAILURE);
	}
	if (!(image->add_image = mlx_get_data_addr(image->img,
			&image->bpp, &image->size_line, &image->endian)))
		return (ft_msg(TM_ERROR, "Recover image", 1, RED));
	tmp = ft_strmjoin("sss", "Loading of '" CYAN, path, RESET "'.");
	ft_msg(TM_INFO, tmp, 0, "");
	wrfree(tmp);
	return (EXIT_SUCCESS);
}

int flaginit_tex(t_data *data, int flag, t_image *img, char *path)
{
	if (flag)
		return (init_texture(data, img, path));
	return (EXIT_SUCCESS);
}
