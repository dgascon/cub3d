/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:33:41 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/05 19:02:28 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	rgb_int(unsigned char alpha, unsigned char red, unsigned char green,
		unsigned char blue)
{
	int	rgb;

	rgb = (int)alpha;
	rgb = (rgb << 8) + (int)red;
	rgb = (rgb << 8) + (int)green;
	rgb = (rgb << 8) + (int)blue;
	return (rgb);
}
