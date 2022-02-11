/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastienlecaille <sebastienlecaille@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:05:35 by dgascon           #+#    #+#             */
/*   Updated: 2022/02/11 17:04:17 by sebastienle      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H
# include "cub3d.h"

typedef	struct			s_screen
{
	t_coord				size;
	unsigned char		sky_color[3];
	unsigned char		floor_color[3];
	int					ceil_tex;
	int					floor_tex;
	int					flag_ceil;
	int					flag_floor;
}						t_screen;

int						init_window(t_data *data);

#endif
