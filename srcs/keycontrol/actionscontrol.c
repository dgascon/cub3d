/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionscontrol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:55:22 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/05 18:58:43 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		lookcontrol(t_data *data)
{
	if (data->actions.lookleft == TRUE)
	{
		data->player.pov += 0.05;
		(data->player.pov > 2 * M_PI) ? data->player.pov = 0 : 0;
	}
	if (data->actions.lookright == TRUE)
	{
		data->player.pov -= 0.05;
		(data->player.pov < 0) ? data->player.pov = 2 * M_PI : 0;
	}
	if (data->actions.lookup == TRUE)
	{
		if (data->player.hdv > -(data->screen.size.y / 7))
			data->player.hdv -= 10;
	}
	if (data->actions.lookdown == TRUE)
	{
		if (data->player.hdv <
			(data->screen.size.y + (data->screen.size.y / 7)))
			data->player.hdv += 10;
	}
}

static void	releasedelay_heightcam(t_data *data, int *state_height_cam)
{
	if (*state_height_cam == 1)
	{
		data->player.height_cam += BLOCK_SIZE / 20;
		(data->player.height_cam > 3 * BLOCK_SIZE / 4) ?
			*state_height_cam = 2 : 0;
	}
	else if (*state_height_cam == 2)
	{
		data->player.height_cam -= BLOCK_SIZE / 20;
		(data->player.height_cam == BLOCK_SIZE / 2) ? *state_height_cam = 0 : 0;
	}
	if (!data->actions.crouching && *state_height_cam == 0)
		data->player.height_cam = BLOCK_SIZE / 2;
}

static void	releasedelay_speed(t_data *data, int *state_speed)
{
	if (*state_speed == 1)
	{
		(data->player.speed < MAX_SPEED) ? data->player.speed += 1 : 0;
		(!data->actions.speed) ? *state_speed = 2 : 0;
	}
	else if (*state_speed == 2)
	{
		data->player.speed -= (BLOCK_SIZE / data->player.speed);
		if (data->player.speed <= MAX_SPEED / 2)
		{
			*state_speed = 0;
			data->player.speed = MAX_SPEED / 2;
		}
	}
}

/*
** Movement gestion
** LookControl
** MoveControl
** jumpControl
** CrouchingControl
** SpeedControl
** ReleaseDelay_heightcam
** ReleaseDelay_speed
*/

void		actionscontrol(t_data *data)
{
	static int state_height_cam = 0;
	static int state_speed = 0;

	lookcontrol(data);
	(data->actions.forward) ? move(data, data->player.pov) : 0;
	(data->actions.backward) ? move(data, data->player.pov - M_PI) : 0;
	(data->actions.leftward) ? move(data, data->player.pov + M_PI_2) : 0;
	(data->actions.rightward) ? move(data, data->player.pov - M_PI_2) : 0;
	if (data->actions.jump && !data->actions.crouching)
		(state_height_cam == 0) ? state_height_cam = 1 : 0;
	if (data->actions.crouching)
	{
		if (data->player.height_cam > BLOCK_SIZE / 4 && state_height_cam == 0)
			data->player.height_cam -= BLOCK_SIZE / 20;
	}
	if (data->actions.speed)
		(state_speed == 0) ? state_speed = 1 : 0;
	releasedelay_heightcam(data, &state_height_cam);
	releasedelay_speed(data, &state_speed);
}
