/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:47:04 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 10:47:06 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

t_st	st_log(t_st st, int fd, const char *fmt, ...)
{
	va_list args;

	if (st == st_error)
		ft_dprintf(fd, "%{red_fg}");
	else if (st == st_fail)
		ft_dprintf(fd, "%{yellow_fg}");
	else if (st == st_succ)
		ft_dprintf(fd, "%{green_fg}");
	else
		ft_dprintf(fd, "%{reset}");
	va_start(args, fmt);
	ft_vadprintf(fd, fmt, args);
	va_end(args);
	ft_dprintf(fd, "%{reset}\n");
	return (st);
}
