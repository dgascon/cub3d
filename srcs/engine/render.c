/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:58:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 20:30:42 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int	select_sprite_color(t_data *data, float proprtion, int wall_row)
{
	t_coord ratio;
	
	float G;
	G = (float)data->Wtex.sizex / 64;
	ratio.y = (int)(proprtion * wall_row) % data->Wtex.sizey;
	ratio.x = (data->raycast.face_detect == 'V') ? (int)(data->raycast.inter.y * G) % data->Wtex.sizex : (int)(data->raycast.inter.x * G) % data->Wtex.sizex;
	return (*(int*)(data->Wtex.add_image + (data->Wtex.size_line * ratio.y) + (ratio.x * sizeof(int))));
}

void	print_sprite(t_data *data)
{
	int row;

	row = data->screen.size.y /2;
	if (data->lst->visible == 1)
	{
					printf("coucou\n");

		while (row < data->screen.size.y + (1/data->lst->dist * 1000))
		{
			*(int*)(data->image.add_image + (row * data->image.size_line) + data->raycast.column * sizeof(int)) = 0x000000;
			row++;
		}
		data->lst->visible = 0;
	}
	
}

int fill_column(t_data *data)
{
	int		height_proj_plane;
	int		row;
	int		wall_row = 0;
	char	*add_opp;
	int		gnagna;
	int		h_max;

	printf("coucou\n");
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	height_proj_plane = floorf(data->player.CST / data->raycast.dist); //REVIEW Optimisation
	gnagna = (float)height_proj_plane / ((float)BLOCK_SIZE / data->player.height_cam); //hauteur sur ratio de la hauteur de la camera 
	row = data->player.hdv - (height_proj_plane - gnagna);//REVIEW Optimisation
	if (row < 0)
	{
		wall_row = 0 - row;
		row = 0;
	}
	h_max = data->player.hdv + gnagna;
	if (h_max > data->screen.size.y)
	{
		h_max = data->screen.size.y;
	}
	float racourcis = (float)data->Wtex.sizey / height_proj_plane;
	while (row < h_max) //REVIEW Optimisation
	{
		*(int*)(add_opp + (row * data->image.size_line)) = select_sprite_color(data, racourcis, wall_row);
		row++;
		wall_row++;
	}
	//TODO faire un recap de toute les variable (surtout les alpha beta gamma)

	print_floor_and_ceil(data, row, gnagna, height_proj_plane, h_max);
	// print_sprite(data);
	return (0);
}
