/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:41:01 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 19:05:16 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"


char    **parsefile(t_data *data, char *file)
{
    int fd;
    char *line;
    int i;
    char **map;
    int never_do = 1;
    int ret;

    i = 1;
    int o = 0;
    line = NULL;
    printf("file =%s\n", file);
    fd = open(file, O_RDONLY);
    if (fd <= 0)
    {
        printf("open error\n");
        return (0);
    }
    map = malloc(10 * sizeof(char *));
    ret = 1;
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        i = 1;
        if (!line)
        {
            printf("GNL error\n");
            return(NULL);
        }
        printf("|%s|\n", line);
        if (line[0]  == 'R')
        {
            data->screen.size.x = ft_atoi(&line[i]);
            while (!(line[i] >= '0' && line[i] <= '9'))
                i++;
            while (line[i] >= '0' && line[i] <= '9')
            {
                i++;
            }
            data->screen.size.y = ft_atoi(&line[i]);
            free(line);
        }
        else
        {
            if (never_do == 1)
            {
                data->world.size.x = ft_strlen(line);
                never_do = 0;
            }
            map[o] = line;
            o++;
//	 free(line);

	}
	map[o] = NULL;
    }
    data->world.size.y = o;
    printf("map y =%d, mapx = %d", data->world.size.y, data->world.size.x);
    close(fd);
    return (map);
}
