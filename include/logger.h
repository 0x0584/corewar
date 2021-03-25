/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:46:33 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 10:46:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include <assert.h>

# include "libft.h"

typedef enum				e_state
{
	st_error = -1,
	st_succ,
	st_fail
}							t_st;

t_st						st_log(t_st st, int fd, const char *fmt, ...);

#endif
