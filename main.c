/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 10:39:46 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/12 17:41:38 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <X11/X.h>

void		resol_max(t_data *data)
{
	int max_x;
	int max_y;
	int state;

	state = 0;
	mlx_get_screen_size(data->mlx.ptr, &max_x, &max_y);
	if (data->screen.size.x > max_x)
	{
		data->screen.size.x = max_x;
		state = 1;
	}
	if (data->screen.size.y > max_y)
	{
		data->screen.size.y = max_y;
		state = 1;
	}
	if (state == 1)
		ft_msg(TM_INFO, "Resizing resolution", 0, YELLOW);
	ft_msg(TM_INFO, "Resolution set.", 0, GREEN);
}

int			init_window(t_data *data)
{
	if (!(data->mlx.ptr = mlx_init()))
		return (ft_msg(TM_ERROR, "MLX", 1, RED));
	resol_max(data);
	if ((data->mlx.win = mlx_new_window(data->mlx.ptr, data->screen.size.x,
			data->screen.size.y, "Dgascon && Nlecaill")) == NULL)
		return (ft_msg(TM_ERROR, "MLX", 1, RED));
	if (!(data->image.img = mlx_new_image(data->mlx.ptr, data->screen.size.x,
			data->screen.size.y)))
		return (ft_msg(TM_ERROR, "MLX", 1, RED));
	if (!(data->image.add_image = mlx_get_data_addr(data->image.img,
			&data->image.bpp, &data->image.size_line, &data->image.endian)))
		return (ft_msg(TM_ERROR, "Recover image", 1, RED));
	return (EXIT_SUCCESS);
}

static void	myloop(t_data *data)
{
	mlx_loop_hook(data->mlx.ptr, scan, data);
	mlx_hook(data->mlx.win, 02, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 03, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, 33, 1L << 17, destroy, data);
	mlx_loop(data->mlx.ptr);
}

int			main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.bmp_save = 0;
	if (ac <= 1)
		return (ft_msg(TM_ERROR, "Argument is missing !", 1, RED));
	else if (ac > 3)
		return (ft_msg(TM_ERROR, "Too much argument", 1, RED));
	(ac == 3 && !ft_strcmp("--save", av[2])) ? data.bmp_save = 1 : 0;
	if (ac == 3 && !data.bmp_save)
		return (ft_msg(TM_ERROR, "Error on 2nd argument", 1, RED));
	data.player = (t_player){.fov = M_PI / 3, .height_cam = BLOCK_SIZE / 2,
		.speed = MAX_SPEED / 2};
	(parsefile(&data, av[1])) ? destroy(&data) : 0;
	data.raycast = (t_raycast) {.alpha = M_PI / 3,
		.delta_ang = (data.player.fov / data.screen.size.x)};
	data.player.dist_proj_plane = ((float)data.screen.size.x / 2) /
		tan(data.player.fov / 2);
	data.player.cst = (BLOCK_SIZE * data.player.dist_proj_plane);
	data.player.hdv = data.screen.size.y / 2;
	ft_msg(TM_INFO, ft_strmjoin("sds", "Number of threads at " ORANGE,
		NB_THREAD, RESET "."), 0, RESET);
	(data.bmp_save) ? scan(&data) : 0;
	myloop(&data);
	return (EXIT_SUCCESS);
}
