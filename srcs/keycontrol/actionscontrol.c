/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   actionscontrol.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 17:55:22 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 20:34:21 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief  test
 * @note   Prout
 * @param  *data: 
 * @retval None
 */
void		lookcontrol(t_data *data)
{
	if (data->actions.lookleft == TRUE)
	{
		data->player.pov += 0.1;
		(data->player.pov > _2PI) ? data->player.pov -= _2PI : 0;
	}
	if (data->actions.lookright == TRUE)
	{
		data->player.pov -= 0.1;
		(data->player.pov < 0) ? data->player.pov += _2PI : 0;
	}
	if (data->actions.lookup == TRUE)
	{
		if (data->player.hdv > -(data->screen.size.y / 7))
			data->player.hdv -= 25;
	}
	if (data->actions.lookdown == TRUE)
	{
		if (data->player.hdv <
			(data->screen.size.y + (data->screen.size.y / 7)))
			data->player.hdv += 25;
	}
}

static void	releasedelay_heightcam(t_data *data, int *state_height_cam)
{
	if (*state_height_cam == 1)
	{
		data->player.height_cam += 5;
		(data->player.height_cam > 48) ? *state_height_cam = 2 : 0;
	}
	else if (*state_height_cam == 2)
	{
		data->player.height_cam -= 5;
		(data->player.height_cam == 32) ? *state_height_cam = 0 : 0;
	}
	if (data->actions.crouching && *state_height_cam == 0)
		data->player.height_cam = 32;
}

static void	releasedelay_speed(t_data *data, int *state_speed)
{
	if (*state_speed == 1)
	{
		data->player.speed += 1;
		(data->player.speed >= MAX_SPEED) ? *state_speed = 2 : 0;
	}
	else if (*state_speed == 2)
	{
		data->player.speed -= 1;
		if (data->player.speed <= 10)
		{
			data->player.speed = 10;
			*state_speed = 0;
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
	if (data->actions.jump)
		(state_height_cam == 0) ? state_height_cam = 1 : 0;
	if (data->actions.crouching)
	{
		if (data->player.height_cam > 22 && state_height_cam == 0)
			data->player.height_cam -= 5;
	}
	if (data->actions.speed)
		(state_speed == 0) ? state_speed = 1 : 0;
	else
		(state_speed == 1) ? state_speed = 2 : 0;
	releasedelay_heightcam(data, &state_height_cam);
	releasedelay_speed(data, &state_speed);
}
