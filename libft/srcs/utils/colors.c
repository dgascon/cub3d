/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:33:41 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/12 17:55:10 by nlecaill         ###   ########lyon.fr   */
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
