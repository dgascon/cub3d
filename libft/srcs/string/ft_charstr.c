/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_charstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 19:40:35 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_charstr(const char hay, const char *needle)
{
	int i;

	i = 0;
	if (!hay || !needle)
		return (0);
	while (needle[i])
	{
		if (hay == needle[i])
			return (1);
		i++;
	}
	return (0);
}
