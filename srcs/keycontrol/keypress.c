/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keypress.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 05:10:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:20:11 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int    key_press(int key, t_data *data)
{
	printf("key = %d\n", key);
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx.ptr, data->mlx.win); //TODO destroy toute les textures
		exit(1);
	}
	if (key == ARROW_LEFT || key == Q)
		data->key.arrow_left = TRUE;
	else if (key == ARROW_RIGHT || key == E)
		data->key.arrow_right = TRUE;
	else if (key == ARROW_UP)
		data->key.arrow_up = TRUE;
	else if (key == ARROW_DOWN)
		data->key.arrow_down = TRUE;
	else if (key == LSHIFT)
		data->key.incspeed = TRUE;
	else if (key == D)
		data->key.D = TRUE;
	else if (key == A)
		data->key.A = TRUE;
	else if (key == W)
		data->key.W = TRUE;
	else if (key == S)
		data->key.S = TRUE;
	else if (key == SHIFT_D)
		data->key.JUMP = TRUE;
	else if (key == ALT_D)
		data->key.SQUAT = TRUE;
	return (0);
}