/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:54:37 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/05 15:30:59 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strlen() function computes the length of the string s.
*/

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
