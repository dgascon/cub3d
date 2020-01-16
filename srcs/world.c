/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   world.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 19:01:39 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 22:42:03 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube3d.h"

void	init_world(t_data *data)
{
	int x, y;

	x = 0;
	y = 0;
	data->world.map[0] = malloc (sizeof(char) * 5 + 1);
	data->world.map[1] = malloc (sizeof(char) * 5 + 1);
	data->world.map[2] = malloc (sizeof(char) * 5 + 1);
	data->world.map[3] = malloc (sizeof(char) * 5 + 1);
	data->world.map[4] = malloc (sizeof(char) * 5 + 1);
	while (y <= 5)
	{
		x = 0;
		while (x <= 5)
		{
			if (x == 5 || y == 5)
				data->world.map[x][y] = 0;
			else if((x > 0 && x < 4 && y > 1 && y < 4) || (x == 2 && y == 1))
			{
				data->world.map[x][y] = '0';
			}
			else
				data->world.map[x][y] = '1';
			x++;
		}
		y++;
	}
	data->world.map[2][3] = 'N';
}
