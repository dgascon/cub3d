/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   world.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 19:01:39 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 19:02:15 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube3d.h"

void	*init_world(t_world *world)
{
	int pX, pY;
	
	pX = 0;
	pY = 0;
	if (!world)
		return (NULL);
	while (pY < 5)
	{
		pX = 0;
		while (pX < 5)
		{
			if ((pX == 0 || pX == 5 - 1 || pY == 0 || pY == 5 - 1))
			{
				world->data[pX][pY] = '1';
			}
			else
			{
				world->data[pX][pY] = '0';
			}
			pX++;
		}
		pY++;
	}
	world->data[1][1] = '1';
	world->data[3][1] = '1';
	world->data[2][3] = 'N';
	world->player.coord.x = 2;
	world->player.coord.y = 3;
	return (world);
}

void	*show_2d_world(t_world *world)
{
	int pX, pY;
	
	pX = 0;
	pY = 0;
	if (!world)
		return (NULL);
	ft_printf("   ");
	while (pX < 5)
	{
		ft_printf(WHITE"[%d]"RESET, pX);
		pX++;
	}
	ft_printf("\n");
	while (pY < 5)
	{
		ft_printf(WHITE"[%d]"RESET, pY);
		pX = 0;
		while (pX < 5)
		{
			if (world->data[pX][pY] == '1')
			{
				ft_printf(RED"[%c]"RESET, world->data[pX][pY]);
			}
			else if(world->data[pX][pY] == '2')
			{
				ft_printf(MAGENTA"[%c]"RESET, world->data[pX][pY]);
			}
			else if (world->data[pX][pY] == 'N')
			{
				ft_printf(GREEN"[%c]"RESET, world->data[pX][pY]);
			}
			else
			{
				ft_printf(BOLDYELLOW"[%c]"RESET, world->data[pX][pY]);
			}
			pX++;
		}
		ft_printf("\n");
		pY++;
	}
	return (world);
}