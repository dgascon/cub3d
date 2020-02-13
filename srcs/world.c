/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   world.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/13 11:48:59 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 11:49:06 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_map(t_data *data, char *line)
{
	char		**tmp_map;
	int			i;
	
	i = 0;
	if (!line)
		return (EXIT_FAILURE);
	data->world.size.y++;
	if (!(tmp_map = wrmalloc(sizeof(char *) * (data->world.size.y))))
	{
		ft_printf("Malloc en y impossible.\n");
		return (EXIT_FAILURE);
	}
	while (i < data->world.size.y - 1)
	{
		if (!(tmp_map[i] = ft_substr(data->world.map[i], 0,
								ft_strlen(data->world.map[i]))))
			return (EXIT_FAILURE);
		i++;
	}
	tmp_map[i] = line;
	(data->world.size.y > 1) ? wrfree(data->world.map[0]) : 0;
	wrfree(data->world.map);
	data->world.map = tmp_map;
   	if (data->world.size.x == 0)
		data->world.size.x = ft_strlen(tmp_map[i]);
	else if (data->world.size.x != (int)ft_strlen(tmp_map[i]))
	{
		ft_printf("Erreur de map\n");
		wrdestroy();
		return (EXIT_FAILURE);
	}
	i = 0;
	while (line[i])
	{
		if (ft_charstr(line[i], "NSWE"))
		{
			if (parse_player(data, line[i],
				(t_coord) {.x = i, .y = data->world.size.y}) <= 0)
				return (EXIT_FAILURE);
		}
		else if(line[i] > '2')
		{
			lsprite_addback(&data->lst, lsprite_new((t_coord){.x = i, .y = data->world.size.y - 1}, data->object[line[i] - 51]));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
