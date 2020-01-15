/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 20:43:05 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** The memmove() function copies len bytes from string src to string dst.
** The two strings may overlap; the copy is always done in a
** non-destructive manner.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*psrc;
	char		*pdst;
	size_t		i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	pdst = dst;
	psrc = src;
	if (psrc < pdst)
		return (ft_memcpy(pdst, psrc, len));
	while (++i < len)
		*(pdst + i) = *(psrc + i);
	return (dst);
}
