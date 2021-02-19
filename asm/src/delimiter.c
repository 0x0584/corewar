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
