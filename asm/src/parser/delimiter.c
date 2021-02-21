/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:33:44 by archid-           #+#    #+#             */
/*   Updated: 2021/02/19 16:58:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delimiter.h"

bool		delimiter(t_deli d)
{
	return d != deli_unknown;
}

bool		is_comment_char(t_deli d)
{
	return (d == deli_eol || d == deli_comment || d == deli_asm_comment);
}


static t_deli	check_prefix(t_deli d)
{

}


t_st			skip_whitespace(const char **ptr)
{
	if (ptr && *ptr && **ptr)
	{
		while (ft_isspace(**ptr))
			*ptr += 1;
		return (st_succ);
	}
	else
	{
		ft_dprintf(2, " %{red_fg}end of line while expecting argument%{reset} \n");
		return (st_error);
	}
}
