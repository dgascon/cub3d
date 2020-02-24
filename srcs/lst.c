/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 04:37:46 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 14:24:42 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_lsprite	*lsprite_new(t_coord pos, t_image texture)
{
	t_lsprite	*ptr;
	int			i;

	i = -1;
	if (!(ptr = wrmalloc(sizeof(t_lsprite))))
		return (0);
	ptr->texture = texture;
	ptr->grd.x = pos.x;
	ptr->grd.y = pos.y;
	ptr->pos.x = (pos.x * BLOCK_SIZE) + BLOCK_SIZE / 2;
	ptr->pos.y = (pos.y * BLOCK_SIZE) + BLOCK_SIZE / 2;
	while (++i < NB_THREAD)
		ptr->visible[i] = 0;
	ptr->next = NULL;
	return (ptr);
}

void		lsprite_addback(t_lsprite **lst, t_lsprite *new)
{
	t_lsprite *list;

	list = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (list->next != NULL)
		{
			list = list->next;
		}
		new->next = NULL;
		list->next = new;
	}
}

t_lsprite	*swap(t_lsprite *ptr1, t_lsprite *ptr2)
{
	t_lsprite	*tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

void		lsprite_sort(t_lsprite **lst)
{
	t_lsprite	**list;
	t_lsprite	*lste;
	t_lsprite	*tmp;
	int			sorted;

	sorted = 0;
	if (lst == NULL || *lst == NULL)
		return ;
	while (sorted != 1)
	{
		sorted = 1;
		list = lst;
		while ((*list) != NULL && (*list)->next != NULL)
		{
			lste = *list;
			tmp = lste->next;
			if (lste->dist < tmp->dist)
			{
				*list = swap(lste, tmp);
				sorted = 0;
			}
			list = (t_lsprite **)&(*list)->next;
		}
	}
}

t_lsprite	*pick_object(t_lsprite *list, t_coord grid)
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
