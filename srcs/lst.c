/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 04:37:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 22:52:18 by nlecaill    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

t_lsprite	*lsprite_new(t_coord pos)
{
	t_lsprite *ptr;

	if (!(ptr = malloc(sizeof(t_lsprite))))
		return (0);
	ptr->grd.x = pos.x;
    ptr->grd.y = pos.y;
    ptr->pos.x = (pos.x * 64) + 32;
    ptr->pos.y = (pos.y * 64) + 32;
    ptr->printed = 0;
    ptr->visible = 0;
	ptr->next = NULL;
	return (ptr);
}

int set_visible(t_lsprite *list, t_coord grid)
{
    t_lsprite *lst;

    lst = list;
    if (lst == NULL)
        return (-1);
    while (lst->next != NULL)
    {
        if (lst->pos.x == grid.x && lst->pos.y == grid.y)
        {
            lst->visible = 1;
            return (1);
        }
        lst = lst->next;
    }
    if (lst->pos.x == grid.x && lst->pos.y == grid.y)
    {
        printf("detected and set\n");
        lst->visible = 1;
        return (1);
    }
    return (-1);
}

t_lsprite *pick_object(t_lsprite *list, t_coord grid)
{
    t_lsprite *lst;

    lst = list;
    if (lst == NULL)
        return (NULL);
    while (lst->next != NULL)
    {
        if (lst->grd.x == grid.y && lst->grd.y == grid.x)
        {
            return (lst);
        }
        lst = lst->next;
    }
    if (lst->grd.x == grid.y && lst->grd.y == grid.x)
    {
        return (lst);
    }
    return (NULL);
}
