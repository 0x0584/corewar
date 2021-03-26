/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:33:44 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:16:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delimiter.h"

bool		delimiter(char c)
{
	return (!c || ft_isspace(c) || is_comment_char(c) || c == deli_comma);
}

bool		is_comment_char(char d)
{
	return (d == deli_eol || d == deli_comment || d == deli_asm_comment);
}

t_st		skip_whitespace(const char **ptr)
{
	if (ptr && *ptr)
	{
		while (ft_isspace(**ptr))
			*ptr += 1;
		if (is_comment_char(**ptr))
			*(char *)*ptr = '\0';
		return (st_succ);
	}
	else
		return (st_log(st_error, 2, "end of parsing: expecting argument"));
}

t_st		seek_delimiter(const char **arg_line,
							const char *walk, bool last_arg)
{
	skip_whitespace(&walk);
	if (*walk && (*walk != deli_comma || (*walk == deli_comma && last_arg)))
		return (st_log(st_error, 2, "end of parsing: unexpected delimiter `%c'", *walk));
	else
	{
		*arg_line = walk + (*walk == deli_comma);
		return (st_succ);
	}
}
