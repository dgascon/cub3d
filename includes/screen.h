/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:05:35 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:21:26 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H
# include "cub3d.h"

typedef struct s_data	t_data;
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
