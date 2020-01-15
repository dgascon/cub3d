/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 15:16:19 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_memchr() function locates the first occurrence of c in string s.
*/

void	*ft_memchr(const void *str, int c, size_t n)
{
	char const	*pstr;
	size_t		i;

	pstr = str;
	i = 0;
	while (i < n)
	{
		if (*(pstr + i) == c)
			return ((void *)&(*(pstr + i)));
		i++;
	}
	return (0);
}
