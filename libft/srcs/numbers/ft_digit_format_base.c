/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_format_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 02:20:32 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 09:19:22 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_digit_format_base(long num, char *base)
{
	int i;
	int	j;
	int moins;
	int sbase;

	moins = 0;
	j = 0;
	sbase = ft_strlen(base);
	i = 0;
	if (num < 0)
		moins = 1;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / sbase;
		if (i % 3 == 1 && num / sbase != 0 && i > 0)
			j++;
		i++;
	}
	return (i + j + moins);
}
