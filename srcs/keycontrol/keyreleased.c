/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keyreleased.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 05:11:12 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:30:57 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int    key_release(int key, t_data *data)
{
	if (key == ARROW_LEFT || key == Q)
		data->key.arrow_left = FALSE;
	else if (key == ARROW_RIGHT || key == E)
		data->key.arrow_right = FALSE;
	else if (key == ARROW_UP)
		data->key.arrow_up = FALSE;
	else if (key == ARROW_DOWN)
		data->key.arrow_down = FALSE;
	else if (key == LSHIFT)
	{
		data->key.incspeed = FALSE;
		data->player.speed = 10;
	}
	else if (key == D)
		data->key.D = FALSE;
	else if (key == A)
		data->key.A = FALSE;
	else if (key == W)
		data->key.W = FALSE;
	else if (key == S)
		data->key.S = FALSE;
	else if (key == SHIFT_D)
		data->key.JUMP = FALSE;
	else if (key == ALT_D)
		data->key.SQUAT = FALSE;
	return (0);
}