/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   floor_and_ceil.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:58:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:30:36 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int floor_and_ceil_color(t_data *data, float calc_const[4], int height_proj_plane, int *val2)
{
	t_coord sol;
	t_coord ceil;
	float dist_mur_sol;
	float dist_mur_plafond;
	float deltaY[2];
	float deltaX[2];
	t_f_coord sincos;

	dist_mur_plafond = calc_const[0] - (calc_const[2] / height_proj_plane);
	dist_mur_sol = calc_const[0] - (calc_const[3] / calc_const[1]);
	sincos.x = 0;
	sincos.y = 0;
	if (data->raycast.face_detect == 'H')
	{
		if (data->raycast.alpha > 0 && data->raycast.alpha < M_PI)
		{
			data->raycast.gamma = data->raycast.alpha - (M_PI_2);
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaY[0] = dist_mur_sol * sincos.y;
			deltaY[1] = dist_mur_plafond * sincos.y;
		}
		else
		{
			data->raycast.gamma = (3 * M_PI_2) - data->raycast.alpha;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaY[0] = dist_mur_sol * sincos.y * -1;
			deltaY[1] = dist_mur_plafond * sincos.y * -1;
		}
		deltaX[0] = dist_mur_sol * sincos.x;
		deltaX[1] = dist_mur_plafond * sincos.x;
	}
	else
	{
		if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < 3 * M_PI_2)
		{
			data->raycast.gamma = M_PI - data->raycast.alpha ;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaX[0] = dist_mur_sol * sincos.y;
			deltaX[1] = dist_mur_plafond * sincos.y;
		}
		else
		{
			data->raycast.gamma = data->raycast.alpha - 2 * M_PI;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaX[0] = dist_mur_sol * sincos.y * -1;
			deltaX[1] = dist_mur_plafond * sincos.y * -1;
		}
		deltaY[0] = dist_mur_sol * sincos.x;
		deltaY[1] = dist_mur_plafond * sincos.x;
	}
	sol.x = (int)(((float)data->ftex.sizex / BLOCK_SIZE) * (data->raycast.inter.x + deltaX[0])) % data->ftex.sizex;
	sol.y = (int)(((float)data->ftex.sizey / BLOCK_SIZE) * (data->raycast.inter.y + deltaY[0])) % data->ftex.sizey;
	ceil.x = (int)(((float)data->rtex.sizex / BLOCK_SIZE) * (data->raycast.inter.x + deltaX[1])) % data->rtex.sizex;
	ceil.y = (int)(((float)data->rtex.sizey / BLOCK_SIZE) * (data->raycast.inter.y + deltaY[1])) % data->rtex.sizey;
	*val2 = *(int*)(data->rtex.add_image + (data->rtex.size_line * ceil.y) + (ceil.x * sizeof(int)));
	return (*(int*)(data->ftex.add_image + (data->ftex.size_line * sol.y) + (sol.x * sizeof(int))));
}
void	print_only_ceil(t_data *data, float val_cst[4], int toto)
{
	int val2;
	char *add_opp;
	int crow = 0;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	while (crow < data->screen.size.y)
	{
		floor_and_ceil_color(data, val_cst, toto, &val2);
		*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
		crow++;
		val_cst[1]++;
		toto++;
	}
}

void    print_floor_and_ceil(t_data *data, int row, int	gnagna, int height_proj_plane, int h_max)
{
    float   cosB;
    float   val_cst[4];
    int		val2;
	int     val1;
    int     crow;
    int     toto;
    char    *add_opp;
    
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
    toto = height_proj_plane - gnagna;
	row = data->player.hdv - toto;
	crow = data->screen.size.y - row;
    cosB = cosf(data->raycast.beta);
	val_cst[0] = (data->raycast.dist / cosB);
	val_cst[1] = gnagna;
	val_cst[2] = (data->player.dist_proj_plane / cosB) * (BLOCK_SIZE - data->player.height_cam);
	val_cst[3] = (data->player.dist_proj_plane / cosB) * (data->player.height_cam);
    row = h_max;
	//TODO faire du cas par cas avec ceil only, floor only
	if (row < crow)
	{
		// quand il y a plus de de sol que de plafond
		if (row < 0) //permet d'avoir 1 condition par colonne plutot que par pixel
		{
			toto -= row;
			val_cst[1] -= row;
			row = 0;
			crow = data->screen.size.y + 1;
		}
		while (row < data->screen.size.y)
		{
			*(int*)(add_opp + (row * data->image.size_line)) = floor_and_ceil_color(data, val_cst, toto, &val2);
			if (crow <= data->screen.size.y)
			{
				*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
				crow++;
			}
			row++;
			val_cst[1]++;
			toto++;
		}
	}
	else
	{
		if (crow < 0)
		{
			toto -= crow;
			val_cst[1] -= crow;
			print_only_ceil(data, val_cst, toto);
			return ;
		}
		while (crow <= data->screen.size.y)
		{
			val1 = floor_and_ceil_color(data, val_cst, toto, &val2);
			*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
			if (row <= data->screen.size.y)
			{
				*(int*)(add_opp + (row * data->image.size_line)) = val1;
				row++;
			}
			crow++;
			val_cst[1]++;
			toto++;
		}
	}
}