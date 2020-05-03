/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:44:47 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/03 15:12:54 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
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
