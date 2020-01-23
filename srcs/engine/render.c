/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:58:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 17:19:41 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int	select_sprite_color(t_data *data, int height_proj_plane, int wall_row)
{
	int val;
	t_d_coord ratio;
	
	val = 0;
	if (!(data->Wtex.img))
	{
		if (!(data->Wtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/bricks64.xpm", &data->Wtex.size, &data->Wtex.size)))
			return (printf("erreur1"));
		if (!(data->Wtex.add_image = mlx_get_data_addr(data->Wtex.img, &data->Wtex.bpp, &data->Wtex.size_line, &data->Wtex.endian)))
			return (printf("erreur2"));
	}
	ratio.y = ((double)data->Wtex.size / (double)height_proj_plane);
	ratio.x = (data->raycast.face_detect == 'V') ? ((int)(data->raycast.inter.y) % 64) : ((int)(data->raycast.inter.x) % 64);
	//printf("height = %d\tratio.y = %f\tratio.x = %d\nx = %f, y = %f\n", height_proj_plane, ratio.y, (int)ratio.x, data->raycast.inter.x, data->raycast.inter.y);
	val = *(int*)(data->Wtex.add_image + (data->Wtex.size_line * (int)(wall_row * ratio.y)) + ((int)ratio.x * sizeof(int)));
	return (val);
}
int floor_color(t_data *data, int row, double dist_proj_plane, int height_proj_plane)
{
	int val;
	t_d_coord sol;
	t_d_coord ratio;
	int dist_mur_sol;
	if (!(data->Ftex.img))
	{
		if (!(data->Ftex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/floor.xpm", &data->Ftex.size, &data->Ftex.size)))
			return (printf("erreur1"));
		if (!(data->Ftex.add_image = mlx_get_data_addr(data->Ftex.img, &data->Ftex.bpp, &data->Ftex.size_line, &data->Ftex.endian)))
			return (printf("erreur2"));
	}
	//sol.y = data->raycast.inter.y + (data->raycast.dist - (dist_proj_plane / (row - ())));
	dist_mur_sol = (data->raycast.dist - (dist_proj_plane / (((double)height_proj_plane / 2) / (double)data->player.height_cam)));
	//dist_mur_sol = 1 / (data->raycast.dist - dist_mur_sol);
	sol.x = data->raycast.inter.x + (data->player.pos.x - (tan(data->raycast.beta) * (data->raycast.dist - dist_mur_sol)));
	sol.y = data->raycast.inter.y + dist_mur_sol;
	ratio.x = (int)sol.x %64;
	ratio.y = (int)sol.y % 64;
	val = *(int*)(data->Ftex.add_image + (int)((double)data->Ftex.size_line * ratio.y) + ((int)ratio.x * sizeof(int)));
	 printf("col = %d\tpos.x = %d pos.y = %d\t sol.x = %f sol.y = %f\talpha = %f\n", data->raycast.column, data->player.pos.x, data->player.pos.y, sol.x, sol.y, data->raycast.alpha);
	return (val);
}

int fill_column(t_data *data)
{
	int height_proj_plane;
	int row;
	double dist_proj_plane;

	//printf("%f\n", data->raycast.dist);
	dist_proj_plane = (data->screen.size.x / 2) / tan(data->player.fov);
	height_proj_plane = floor((BLOCK_SIZE * dist_proj_plane) / data->raycast.dist); //REVIEW Optimisation
	(height_proj_plane > data->screen.size.y) ? height_proj_plane = data->screen.size.y : 0;
	row = (data->screen.size.y / 2 ) - (height_proj_plane / 2);//REVIEW Optimisation
	if (data->raycast.face_detect == 'V')
		data->image.colors = rgb_int(168, 15, 119);
	else if (data->raycast.face_detect == 'H')
		data->image.colors = rgb_int(80, 26, 62);
		int wall_row = 0;
	while (row < (data->screen.size.y / 2) + (height_proj_plane / 2)) //REVIEW Optimisation
	{
		*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = select_sprite_color(data, height_proj_plane, wall_row); //RGB
		row++;
		wall_row++;
	}
	while (row < data->screen.size.y)
	{
		*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = floor_color(data, row, dist_proj_plane, height_proj_plane);
		row++;
	}
	return (0);
}