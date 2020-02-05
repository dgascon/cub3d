/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keypress.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 05:10:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 17:18:01 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int    key_press(int key, t_data *data)
{
	if (key == ESC)
		destroy(data);
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
	else if (key == Z)
		data->player.show_minimap = !data->player.show_minimap;
	return (0);
}