/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/20 02:40:13 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 16:35:16 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list ap;
	int		i;
	t_pf	tpf;

	i = 0;
	va_start(ap, str);
	tpf.length = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			pf_initlst(&ap, &tpf);
			i += pf_conv(&tpf, str + i + 1);
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			tpf.length++;
		}
		i++;
	}
	va_end(ap);
	return (tpf.length);
}
