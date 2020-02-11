/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/11 15:08:05 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:08:10 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_player(t_data *data, char direction, t_coord position)
{
	if (data->player.pos.x != 0 && data->player.pos.y != 0)
	{
		ft_printf("Deux joueurs de placé sur la carte !\n");
		freemap(data, 0);
		free(data->world.map);
		return (-1);
	}
	if (direction == 'N')
		data->player.pov = POV_NORTH;
	else if (direction == 'E')
		data->player.pov = POV_EAST;
	else if (direction == 'S')
		data->player.pov = POV_SOUTH;
	else if (direction == 'W')
		data->player.pov = POV_WEST;
	data->player.pos.x = (BLOCK_SIZE * position.x) + 32;
	data->player.pos.y = (BLOCK_SIZE * position.y) - 32;
	return (1);
}