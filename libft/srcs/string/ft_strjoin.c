/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 14:53:41 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 15:46:24 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	maxsize;
	size_t	sizes1;

	if (s1 == 0 && s2 != 0)
		return (ft_strdup(s2));
	if (s2 == 0 && s1 != 0)
		return (ft_strdup(s1));
	sizes1 = ft_strlen(s1);
	maxsize = sizes1 + ft_strlen(s2) + 1;
	if ((s1 == 0 && s2 == 0) || !(ptr = malloc(maxsize * sizeof(char))))
		return (NULL);
	ft_strcat(ptr, s1);
	ft_strcat(ptr, s2);
	return (ptr);
}
