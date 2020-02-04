/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   garbage.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 05:09:05 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

t_lsprite	*lsprite_new(t_coord pos)
{
	t_lsprite *ptr;

	if (!(ptr = malloc(sizeof(t_lsprite))))
		return (0);
	ptr->pos.x = pos.x;
    ptr->pos.y = pos.y;
	ptr->next = NULL;
	return (ptr);
}

int isin_lst(t_lsprite *list, t_coord grid)
{
    t_lsprite *lst;

    lst = list;
    if (lst == NULL)
        lst = lsprite_new(grid);
    while (lst->next != NULL)
    {
        if (lst->pos.x == grid.x && lst->pos.y == grid.y)
            return (1);
        lst = lst->next;
    }
    if (lst->pos.x == grid.x && lst->pos.y == grid.y)
            return (1);
    return (0);
}
