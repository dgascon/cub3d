/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:34:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/10 10:08:48 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_texture(t_data *data, t_image *image)
{
	char *tmp;

	if (!(image->path) || !(ft_strcmp(image->path, "")))
		return (EXIT_SUCCESS);
	if (!(image->img = mlx_xpm_file_to_image(data->mlx.ptr, image->path,
			&image->size.x, &image->size.y)))
	{
		tmp = ft_strmjoin("sss", "Texture not found. ('", image->path, "').");
		ft_msg(TM_ERROR, tmp, 1, RED);
		wrfree(tmp);
		return (EXIT_FAILURE);
	}
	if (!(image->add_image = mlx_get_data_addr(image->img,
			&image->bpp, &image->size_line, &image->endian)))
		return (ft_msg(TM_ERROR, "Recover image", 1, RED));
	tmp = ft_strmjoin("sss", "Loading of '" CYAN, image->path, RESET "'.");
	ft_msg(TM_INFO, tmp, 0, "");
	wrfree(tmp);
	return (EXIT_SUCCESS);
}

int		parse_set_tex(t_data *data, char **line)
{
	if (data->world.map)
		return (ft_msg(TM_ERROR, "The map must be defined last.", 1, RED));
	if (!line[1] || !line[0])
		return (ft_msg(TM_ERROR, "Bad param format.", 1, RED));
	else if (ft_charstr(line[0][0], "FC"))
		return (parse_floor_ceil(data, line));
	else if ((line[0][0] == 'N' && line[0][1] == 'O') &&
		dup_path(&data->w_tex[0], line[1]))
		return (EXIT_FAILURE);
	else if ((line[0][0] == 'W' && line[0][1] == 'E') &&
		dup_path(&data->w_tex[3], line[1]))
		return (EXIT_FAILURE);
	else if ((line[0][0] == 'E' && line[0][1] == 'A') &&
		dup_path(&data->w_tex[1], line[1]))
		return (EXIT_FAILURE);
	else if (line[0][0] == 'V' && dup_path(&data->hud_tex[0], line[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		dup_path(t_image *image, char *line)
{
	if ((image)->valid == 1)
		return (ft_msg(TM_ERROR, "Double argument to parsing !", 1, RED));
	(image)->path = ft_strdup(line);
	(image)->valid = 1;
	return (EXIT_SUCCESS);
}
