/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 03:54:23 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strncmp() function compares not more than n characters.
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*st1;
	const unsigned char	*st2;
	size_t				i;

	st1 = (const unsigned char *)s1;
	st2 = (const unsigned char *)s2;
	i = 0;
	while (i < n && (*(st1 + i) || *(st2 + i)))
	{
		if (*(st1 + i) != *(st2 + i))
			return (*(st1 + i) - *(st2 + i));
		i++;
	}
	return (0);
}
