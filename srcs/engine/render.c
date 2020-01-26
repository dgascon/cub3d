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
int floor_color(t_data *data, double dist_proj_plane, int height_proj_plane, int *val2)
{
	int val;
	t_d_coord sol;
	t_d_coord ratio;
	double dist_mur_sol;
	double deltaY;
	double deltaX;
	if (!(data->Ftex.img))
	{
		if (!(data->Ftex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/vitrail-3.xpm", &data->Ftex.size, &data->Ftex.size)))
			return (printf("erreur1"));
		if (!(data->Ftex.add_image = mlx_get_data_addr(data->Ftex.img, &data->Ftex.bpp, &data->Ftex.size_line, &data->Ftex.endian)))
			return (printf("erreur2"));
	}
	if (!(data->Rtex.img))
	{
		if (!(data->Rtex.img = mlx_xpm_file_to_image(data->mlx.ptr, "assets/images/ice.xpm", &data->Rtex.size, &data->Rtex.size)))
			return (printf("erreur1"));
		if (!(data->Rtex.add_image = mlx_get_data_addr(data->Rtex.img, &data->Rtex.bpp, &data->Rtex.size_line, &data->Rtex.endian)))
			return (printf("erreur2"));
	}
	dist_mur_sol = ((data->raycast.dist / (cos(data->raycast.beta))) - (((dist_proj_plane / cos(data->raycast.beta))/ (((double)height_proj_plane) / (double)data->player.height_cam))));
	if (data->raycast.face_detect == 'H')
	{
		if (data->raycast.alpha > 0 && data->raycast.alpha < M_PI)
		{
			data->raycast.gamma = data->raycast.alpha - (M_PI / 2);
			deltaY = dist_mur_sol * cos(data->raycast.gamma);
		}
		else
		{
			data->raycast.gamma = (3* M_PI / 2) - data->raycast.alpha;
			deltaY = dist_mur_sol * cos(data->raycast.gamma) * -1;
		}
		
		deltaX = dist_mur_sol * sin(data->raycast.gamma);
	}
	else
	{
		if (data->raycast.alpha > M_PI / 2 && data->raycast.alpha < 3*M_PI/2)
		{

			data->raycast.gamma = M_PI- data->raycast.alpha ;
			deltaX = dist_mur_sol * cos(data->raycast.gamma);
		}
		else
		{
			data->raycast.gamma = data->raycast.alpha - 2*M_PI ;
			deltaX = dist_mur_sol * cos(data->raycast.gamma) * -1;
		}
		deltaY = dist_mur_sol * sin(data->raycast.gamma);
	}
	sol.x = data->raycast.inter.x + deltaX - data->player.pos.x/2;
	sol.y =(data->raycast.inter.y + deltaY) - data->player.pos.y/2; // ca vient de data->player.pos.X
		ratio.x = (int)sol.x % 64;
		ratio.y = (int)sol.y % 64;

	
	val = *(int*)(data->Ftex.add_image + (int)((double)data->Ftex.size_line * ratio.y) + ((int)ratio.x * sizeof(int)));
	*val2 = *(int*)(data->Rtex.add_image + (int)((double)data->Rtex.size_line * ratio.y) + ((int)ratio.x * sizeof(int)));
	static int once = 0;
	if (data->raycast.column == (data->screen.size.x / 2) && once < 2)
	{
		val = 0xFF0000;
		printf("\nsol.x = %f\t sol.y = %f\t pos.x = %d\t pos.y = %d\tdist_mur_sol=%f\tdist = %f\tdeltaY = %f\n", sol.x, sol.y, data->player.pos.x, data->player.pos.y, dist_mur_sol, data->raycast.dist, deltaY);
		once++;
	}
	return (val);
}

int fill_column(t_data *data)
{
	int height_proj_plane;
	int row;
	double dist_proj_plane;

	
	dist_proj_plane = (data->screen.size.x / 2) / tan(data->player.fov);
	height_proj_plane = floor((BLOCK_SIZE * dist_proj_plane) / data->raycast.dist); //REVIEW Optimisation
	height_proj_plane *= 2;
	row = (data->screen.size.y / 2 ) - (height_proj_plane / 2);//REVIEW Optimisation
	int wall_row = 0;
	while (row < (data->screen.size.y / 2) + (height_proj_plane / 2)) //REVIEW Optimisation
	{
		if (row >= 0 && row < data->screen.size.y)
		*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = select_sprite_color(data, height_proj_plane, wall_row); //RGB
		row++;
		wall_row++;
	}
	wall_row =height_proj_plane / 2;
	int val2;
	while (row < data->screen.size.y)
	{
		*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = floor_color(data, dist_proj_plane, wall_row, &val2);
		*(int*)(data->image.add_image + (data->image.size_line * (data->screen.size.y/2 - (row - data->screen.size.y/2))) + data->raycast.column * sizeof(int)) = val2;
		wall_row++;
		row++;
	}
	return (0);
}