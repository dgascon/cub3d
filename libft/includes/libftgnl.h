/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libftgnl.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/20 18:32:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 13:20:28 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFTGNL_H
# define LIBFTGNL_H
# define ERROR -1
# define SUCCESS 1
# define ENDFILE 0
# include <fcntl.h>

typedef struct	s_gnl
{
	int				fd;
	char			*buffer;
	struct s_gnl	*next;
}				t_gnl;

int				gnl_line(char *buffer, char **line, int index);
int				get_next_line(int fd, char **line);
#endif
