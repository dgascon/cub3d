/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_substr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 12:33:51 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	maxsize;

	i = -1;
	if (s == 0)
		return (NULL);
	maxsize = (start >= ft_strlen(s)) ? 0 : len;
	if (!(substr = malloc((maxsize + 1) * sizeof(char))))
		return (NULL);
	while (++i < maxsize && s[start + i])
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
