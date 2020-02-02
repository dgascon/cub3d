/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 14:53:41 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 02:10:14 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	sizes1;
	size_t	sizes2;
	size_t	i;

	if (s1 == 0 && s2 != 0)
		return (ft_strdup(s2));
	if (s2 == 0 && s1 != 0)
		return (ft_strdup(s1));
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	if ((s1 == 0 && s2 == 0)
	|| !(ptr = malloc((sizes1 + sizes2 + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < sizes1)
		ptr[i] = s1[i];
	i = -1;
	while (++i < sizes2)
		ptr[i + sizes1] = s2[i];
	ptr[sizes2 + sizes1] = '\0';
	return (ptr);
}
