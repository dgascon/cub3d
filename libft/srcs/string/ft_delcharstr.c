/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delcharstr.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:26:06 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 02:16:03 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delcharstr(char *line, char *charset)
{
	int		i;
	char	*tmp;
	char	*linechar;
	char	*ret;

	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if (!(ft_charstr(line[i], charset)))
		{
			linechar = ft_chartostr(line[i]);
			ret = ft_strjoin(tmp, linechar);
			free(linechar);
			free(tmp);
			tmp = ret;
		}
		i++;
	}
	return (ret);
}
