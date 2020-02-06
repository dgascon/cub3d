/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keyreleased.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 05:11:12 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 18:16:34 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void    key_release(int key, t_data *data)
{
	if (key == ARROW_LEFT || key == Q)
		data->actions.lookleft = FALSE;
	else if (key == ARROW_RIGHT || key == E)
		data->actions.lookright = FALSE;
	else if (key == ARROW_UP)
		data->actions.lookup = FALSE;
	else if (key == ARROW_DOWN)
		data->actions.lookdown = FALSE;
	else if (key == LSHIFT)
	{
		data->actions.speed = FALSE;
		data->player.speed = 10;
	}
	else if (key == D)
		data->actions.rightward = FALSE;
	else if (key == A)
		data->actions.leftward = FALSE;
	else if (key == W)
		data->actions.forward = FALSE;
	else if (key == S)
		data->actions.backward = FALSE;
	else if (key == SHIFT_D)
		data->actions.jump = FALSE;
	else if (key == ALT_D)
		data->actions.crouching = FALSE;
	return (0);
}