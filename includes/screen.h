/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:05:35 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 16:58:51 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H
# include "cub3d.h"

typedef struct s_data	t_data;
typedef	struct			s_screen
{
	t_coord		size;
	unsigned char		sky_color[3];
	unsigned char		floor_color[3];
	int			CF_textured;
}						t_screen;

int						init_window(t_data *data);

#endif
