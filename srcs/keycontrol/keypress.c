/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keypress.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 05:10:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:47:21 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int    key_press(int key, t_data *data)
{
	if (key == ESC)
		destroy(data);
	if (key == ARROW_LEFT || key == Q)
		data->actions.lookleft = TRUE;
	else if (key == ARROW_RIGHT || key == E)
		data->actions.lookright = TRUE;
	else if (key == ARROW_UP)
		data->actions.lookup = TRUE;
	else if (key == ARROW_DOWN)
		data->actions.lookdown = TRUE;
	else if (key == LSHIFT)
		data->actions.speed = TRUE;
	else if (key == D)
		data->actions.rightward = TRUE;
	else if (key == A)
		data->actions.leftward = TRUE;
	else if (key == W)
		data->actions.forward = TRUE;
	else if (key == S)
		data->actions.backward = TRUE;
	else if (key == SPACE)
		data->actions.jump = TRUE;
	else if (key == LCTRL)
		data->actions.crouching = TRUE;
	else if (key == M)
		data->player.show_minimap = !data->player.show_minimap;
	return (0);
}