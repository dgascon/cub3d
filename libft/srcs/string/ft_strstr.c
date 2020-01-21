/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 13:44:47 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstr(const char *hay, const char *needle)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!hay || !needle)
		return (0);
	while (hay[i])
	{
		while (needle[j])
		{
			if (hay[i] == needle[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
