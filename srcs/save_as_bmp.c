/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_as_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:21:51 by nlecaill          #+#    #+#             */
/*   Updated: 2020/05/01 10:48:33 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_bmp_params(t_data *data, unsigned int uval[15])
{
	uval[0] = (54) + (data->screen.size.x * data->screen.size.y * 3);
	uval[1] = 0x0000;
	uval[2] = 54;
	uval[3] = 40;
	uval[4] = data->screen.size.x;
	uval[5] = data->screen.size.y;
	uval[6] = 0x00000001;
	uval[7] = 0x0018;
	uval[8] = 0x0000;
	uval[9] = data->screen.size.x * data->screen.size.y * 3;
	uval[10] = 0xEC4;
	uval[11] = 0xEC4;
	uval[12] = 0x00;
	uval[13] = 0x00;
}

static void	complete_line(int fd, int i, int *nb_octet)
{
	unsigned char	fill;

	fill = 0x00;
	if (i % 4 == 1)
		*nb_octet += write(fd, &fill, 1);
	if (i % 4 >= 1 && i % 4 <= 2)
		*nb_octet += write(fd, &fill, 1);
	fill = 0xFF;
	if (i % 4 != 0)
		*nb_octet += write(fd, &fill, 1);
}

static int	fill_img_bmp(t_data *data, unsigned int uval[15],
							int *nb_octet, int fd)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = -1;
	y = data->screen.size.y;
	while (--y >= 0)
	{
		i = 0;
		while (++x < data->screen.size.x)
		{
			uval[0] = *(int *)(data->image.add_image
			+ (data->image.size_line * y) + (x * sizeof(int)));
			*nb_octet += write(fd, &uval[0], 3);
			i += 3;
		}
		complete_line(fd, i, nb_octet);
		x = -1;
	}
	return (0);
}

static void	save_bmp_2(int *i, unsigned int *uval)
{
	i[0] = -1;
	while (++i[0] < 6)
		i[3] += write(i[1], &uval[i[0]], 4);
	while (i[0] < 8)
		i[3] += write(i[1], &uval[i[0]++], 2);
	while (i[0] < 14)
		i[3] += write(i[1], &uval[i[0]++], 4);
}

void		save_bmp(t_data *data)
{
	int				i[4];
	unsigned int	uval[15];

	ft_bzero(&*(i + 2), 8);
	while ((i[1] = open(ft_strmjoin("sds", "save", i[2], ".bmp"),
	O_WRONLY | O_CREAT | O_EXCL, 00644)) <= 0)
		i[2]++;
	init_bmp_params(data, uval);
	i[3] = write(i[1], "BM", 2);
	if (i[3] < 2)
	{
		ft_msg(TM_ERROR, "Writing file\n", -1, RED);
		destroy(data);
	}
	save_bmp_2(i, uval);
	fill_img_bmp(data, uval, &i[3], i[1]);
	close(i[1]);
	ft_msg(TM_INFO, ft_strmjoin("sdsds", "Writing of ", i[3],
	" bytes in the save file", i[2], ".bmp finished."), 1, GREEN);
	destroy(data);
}
