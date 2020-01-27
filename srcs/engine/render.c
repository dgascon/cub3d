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
	ratio.y = (int)(((double)data->Wtex.size / (double)height_proj_plane) * wall_row) % 64;
	ratio.x = (data->raycast.face_detect == 'V') ? ((int)(data->raycast.inter.y) % 64) : ((int)(data->raycast.inter.x) % 64);
	//printf("height = %d\tratio.y = %f\tratio.x = %d\nx = %f, y = %f\n", height_proj_plane, ratio.y, (int)ratio.x, data->raycast.inter.x, data->raycast.inter.y);
	val = *(int*)(data->Wtex.add_image + (data->Wtex.size_line * (int)(ratio.y)) + ((int)ratio.x * sizeof(int)));
	if (ratio.x == 0)
	{
		val = 0;
	}
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
	sol.x = (data->raycast.inter.x + deltaX); //- (double)data->player.pos.x/2  + BLOCK_SIZE;
	sol.y = (data->raycast.inter.y + deltaY); //- (double)data->player.pos.y/2; // ca vient de data->player.pos.X
	ratio.x = (int)floor(sol.x) % 64;
	ratio.y = (int)floor(sol.y) % 64;

	
	val = *(int*)(data->Ftex.add_image + (int)((double)data->Ftex.size_line * ratio.y) + ((int)ratio.x * sizeof(int)));
	*val2 = *(int*)(data->Rtex.add_image + (int)((double)data->Rtex.size_line * ratio.y) + ((int)ratio.x * sizeof(int)));
	return (val);
}

int fill_column(t_data *data)
{
	int height_proj_plane;
	int row;
	
	height_proj_plane = floor((BLOCK_SIZE * data->player.dist_proj_plane) / data->raycast.dist); //REVIEW Optimisation
	row = (data->screen.size.y / 2 ) - (height_proj_plane);//REVIEW Optimisation
	//printf("dist = %f\theight = %d\tpox = %d pos y = %d\t dist_proj_plane = %f\n",data->raycast.dist, height_proj_plane, data->player.pos.x, data->player.pos.y, data->player.dist_proj_plane);
	int wall_row = 0;
	while (row < (data->screen.size.y / 2) + (height_proj_plane / 2)) //REVIEW Optimisation
	{
		if (row >= 0 && row < data->screen.size.y)
			*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = select_sprite_color(data, height_proj_plane, wall_row); //RGB
		row++;
		wall_row++;
	}
	height_proj_plane/=2;
	int val2;
	while (row < data->screen.size.y)
	{
		*(int*)(data->image.add_image + (row * data->image.size_line) + (data->raycast.column * sizeof(int))) = floor_color(data, data->player.dist_proj_plane, height_proj_plane, &val2);
		*(int*)(data->image.add_image + (data->image.size_line * (data->screen.size.y/2 - (row - data->screen.size.y/2))) + data->raycast.column * sizeof(int)) = val2;
		height_proj_plane++;
		row++;
	}
	return (0);
}