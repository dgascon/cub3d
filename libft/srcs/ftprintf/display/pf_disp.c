/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_disp.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 17:43:51 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 16:35:03 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	length_calc(t_pf *tpf, int count, ...)
{
	int		x;
	va_list ap;

	va_start(ap, count);
	while (count--)
	{
		x = va_arg(ap, int);
		tpf->length += (x > 0) ? x : 0;
	}
	va_end(ap);
}
