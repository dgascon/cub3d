/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:34:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 09:17:37 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_texture(t_data *data, t_image *image, char *path)
{
	char *msg;

	
	if (!(image->img = mlx_xpm_file_to_image(data->mlx.ptr, path,
			&image->size.x, &image->size.y)))
	{
		msg = "L'image n'existe pas. ('";
		msg = ft_strjoin(msg, path);
		msg = ft_strjoin(msg, "').");
		ft_msg(TM_ERROR, msg, 1, RED);
		wrfree(msg);
		return (EXIT_FAILURE);
	}
	if (!(image->add_image = mlx_get_data_addr(image->img,
			&image->bpp, &image->size_line, &image->endian)))
		return (ft_msg(TM_ERROR, "Recuperation de l'image", 1, RED));
	msg = "Chargement de '" CYAN;
	msg = ft_strjoin(msg, path);
	msg = ft_strjoin(msg, RESET "'.");
	return (ft_msg(TM_INFO, msg, 0, ""));
}

int flaginit_tex(t_data *data, int flag, t_image *img, char *path)
{
	if (flag)
		return (init_texture(data, img, path));
	return (EXIT_SUCCESS);
}
