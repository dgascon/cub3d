/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_byte.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:16:48 by nlecaill          #+#    #+#             */
/*   Updated: 2020/02/24 14:21:12 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_index_byte(void *adresse, int nb_byte, int index)
{
	unsigned char byte;

	byte = -1;
	if (nb_byte == 1)
		byte = *(char*)adresse;
	else if (nb_byte == 4 && (index <= 3 && index >= 0))
		byte = *(unsigned int*)adresse >> (index * 8);
	else if (nb_byte == 8 && (index <= 7 && index >= 0))
		byte = *(unsigned long*)adresse >> (index * 8);
	return (byte);
}

void	*get_index_adresse(void *adresse, int nb_byte, int index)
{
	void *byte;

	byte = NULL;
	if (nb_byte == 1)
		byte = adresse;
	else if (nb_byte == 4 && (index <= 3 && index >= 0))
		byte = adresse + (index);
	else if (nb_byte == 8 && (index <= 7 && index >= 0))
		byte = adresse + index;
	return (byte);
}
