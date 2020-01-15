/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd_front.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 08:23:46 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *enew)
{
	if (!alst || !enew)
		return ;
	enew->next = *alst;
	*alst = enew;
}
