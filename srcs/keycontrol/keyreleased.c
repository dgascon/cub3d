/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyreleased.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 05:11:12 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:22:12 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int key, t_data *data)
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
		data->actions.speed = FALSE;
	else if (key == D)
		data->actions.rightward = FALSE;
	else if (key == A)
		data->actions.leftward = FALSE;
	else if (key == W)
		data->actions.forward = FALSE;
	else if (key == S)
		data->actions.backward = FALSE;
	else if (key == SPACE)
		data->actions.jump = FALSE;
	else if (key == LCTRL)
		data->actions.crouching = FALSE;
	return (0);
}
