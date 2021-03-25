/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:22:26 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:27:09 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static t_st		parse_header(const char *line)
{
	const char		*walk;
	t_st			st;

	walk = line;
	st = st_fail;
	skip_whitespace(&line);
	if (!*walk)
		return (st_fail);
	else if ((st = match_name(line)) == st_succ)
		return (g_header_status <= 2 ? st_succ : st_error);
	else if (st == st_error)
		return (st_error);
	else if ((st = match_comment(line)) == st_succ)
		return (g_header_status <= 2 ? st_succ : st_error);
	else if (st == st_error)
		return (st_error);
	else
		return (st_fail);
}

t_st			parse_line(char **line)
{
	t_st			st;

	if (!line || !*line)
		return (st_error);
	else if ((st = parse_header(*line)) == st_error)
		return (st_error);
	else if (st == st_succ)
		return (st_fail);
	else if (is_comment_char(*line[0]))
		return (st_fail);
	else
		return (st_succ);
}

t_hash			g_labels = NULL;
t_champ			g_champ;
int				g_header_status = 0;
t_u8			g_name[PROG_NAME_LENGTH + 1];
