/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_as_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:21:51 by nlecaill          #+#    #+#             */
/*   Updated: 2020/02/17 16:39:27 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     save_bmp(t_data *data)
{
		int fd;
		int i;
		int val;
		unsigned uval;

		i = 0;
		if ((fd = open("save.bmp", O_WRONLY | O_CREAT, 00644)) <= 0)
			return (ft_msg(TM_ERROR, "Impossible to create .BMP file! Maybe already exist", 1, RED));
		// printf("open\n");
		//fill_the_header_file
		if (write(fd, "BM", 2) < 2) //signature sur 2octet
			return (ft_msg(TM_ERROR, "ERROR\n", 1, RED));
		// printf("firts\n");
		uval = (14) + (40) + (data->screen.size.x * data->screen.size.y * 3); //taille total du fichier en octet sur 4octet
		if ( write(fd, &uval, 4) < 1)
			 return (ft_msg(TM_ERROR, "ERRORe\n", 1, RED));

		val = 0x00;                //champs reserver 4octet
		write(fd, &val, 4);
		uval = 54;              //offet de l'image 4octet
		write(fd, &uval, 4);
		// printf("head\n");
		//fill_the_image_header
		uval = 40;                       //image_header_size 4octet
			write(fd, &uval, 4);
		val = data->screen.size.x;       //nb_pixel_H 4octet
			write(fd, &val, 4);
		val = data->screen.size.y;       //nb_pixel_V 4octet
			write(fd, &val, 4);
		uval = 1;                        //nb_plans 2octet (vaut toujours 1)
			write(fd, &uval, 2);
		uval = 24;                       //profondeur de couleur en nombre de bits 2octets 32bits pour nous )
			write(fd, &uval, 2);
		uval = 0;                        				//methode de compression sur 4octets (val 0 pour nous)
			write(fd, &uval, 4);
		uval = (data->screen.size.x * data->screen.size.y * sizeof(int)); //taille total de l'image en octet 4octets
			write(fd, &uval, 4);
		val = 0xEC4;											//resolution horizontal (nb pixel/metre) sur 4octets
			write(fd, &val, 4);
		val = 0xEC4;											//resolution vertical (nb_pixel / metre) sur 4 octets
			write(fd, &val, 4);
		uval = 0;    //nb_couleur palette 4octets
			write(fd, &uval, 4);
		uval = 0;    //nb_color_importante de palette (peut etre egal a 0) sur 4octets	
			write(fd, &uval, 4);
		// printf("headimg\n");
		//fill_the_palette
			//palette is optionnal skip this shit
		//fill_the_image
		int x = 0;
		int y = data->screen.size.y;
		unsigned char fill;
		
		while (--y >= 0)
		{
			i = 0;
			// printf("ligne: %d\n", y);
			while(x < data->screen.size.x)
			{
				val = *(int *)(data->image.add_image + (data->image.size_line * y) + (x * sizeof(int)));
				write(fd, &val, 3);
				x++;
				i += 3;
			}
			fill = 0x00;
			if (i % 4 == 1)
			{
				write(fd, &fill, 1);
			}
			if (i % 4 >= 1 && i%4 <= 2)
			{
				write(fd, &fill, 1);
			}
			if (i % 4 != 0)
			{
				fill = 0xFF;
				write(fd, &fill, 1);
			}
			x = 0;
		}
		close(fd);
		
		/*Les images en couleurs réelles utilisent 24 bits par pixel, ce qui signifie qu'il faut 3 octets pour coder chaque pixel, en prenant soin de respecter l'ordre de l'alternance bleu, vert et rouge.
			i%4 == 1 00 00 FF
			i%4 == 2 00 FF
			i %4 ==3 FF
			Chaque ligne de l'image doit comporter un nombre total d'octets qui soit 
			un multiple de 4; si ce n'est pas le cas, la ligne doit être complétée par des 0 de telle manière à respecter ce critère. 
		*/
		
		return (0);
}