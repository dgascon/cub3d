/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_geometrical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:20:46 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:21:44 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_rect(t_image *image, t_coord pos, t_coord size, int colors)
{
	t_coord tmp;

	tmp.y = 0;
	while (tmp.y < size.y)
	{
		tmp.x = 0;
		while (tmp.x < size.x)
		{
			*(int*)(image->add_image + (tmp.x + pos.x) * sizeof(int) +
				((tmp.y + pos.y) * image->size_line)) = colors;
			tmp.x++;
		}
		tmp.y++;
	}
}
