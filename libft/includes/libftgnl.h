/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgnl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:32:02 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 09:18:09 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGNL_H
# define LIBFTGNL_H
# define ERROR -1
# define SUCCESS 1
# define ENDFILE 0
# include <fcntl.h>

typedef struct	s_gnl_lc
{
	int				fd;
	char			*buffer;
	struct s_gnl_lc	*next;
}				t_gnl_lc;

typedef struct	s_gnl
{
	int			fd;
	char		*line;
	int			ret;
}				t_gnl;

int				gnl_line(char *buffer, char **line, int index);
int				get_next_line(int fd, char **line);
int				checkformatfile(char *file, t_gnl *gnl, char *ext);
#endif
