/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:58:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:30:13 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

//A bouger
static int	rgb_int(int red, int green, int blue)
{
	int	rgb;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	select_sprite_color(t_data *data)
{
	mlx_xpm_file_to_image(data->mlx.ptr, "bricks64.xpm", );
	return (val);
}

int fill_column(t_data *data)
{
	int height_proj_plane;
	int row;
	double dist_proj_plane;

	dist_proj_plane = (data->screen.size.x / 2) / tan(data->player.fov);
	height_proj_plane = floor((BLOCK_SIZE * dist_proj_plane) / data->raycast.dist); //REVIEW Optimisation
	(height_proj_plane > data->screen.size.y) ? height_proj_plane = data->screen.size.y : 0;
	row = (data->screen.size.y / 2 ) - (height_proj_plane / 2);//REVIEW Optimisation
	if (data->raycast.face_detect == 'V')
		data->image.colors = rgb_int(168, 15, 119);
	else if (data->raycast.face_detect == 'H')
		data->image.colors = rgb_int(80, 26, 62);
	while (row < (data->screen.size.y / 2) + (height_proj_plane / 2)) //REVIEW Optimisation
	{
		*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = select_sprite_color(data); //RGB
		row++;
	}
	return (0);
}