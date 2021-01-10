/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:15:06 by archid-           #+#    #+#             */
/*   Updated: 2019/11/22 18:56:36 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

int		ft_dprintf(const int fd, const char *fmt, ...)
{
	va_list args;
	t_buff	*buff;
	t_list	*lstfrmt;
	int		n_chars;

	lstfrmt = NULL;
	n_chars = 0;
	if (!(buff = buff_alloc(0x20)))
		return (-1);
	va_start(args, fmt);
	format_parse(fmt, &lstfrmt);
	format_populate(&lstfrmt, &args);
	n_chars = format_to_buff(lstfrmt, buff);
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	if (n_chars >= 0)
		n_chars += buff_write(fd, buff);
	buff_free(&buff);
	return (n_chars);
}
