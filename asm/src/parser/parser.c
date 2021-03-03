/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:22:26 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 17:48:24 by archid-          ###   ########.fr       */
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
	else if ((st = match_name(line)) == st_fail)
	{
		if ((st = match_comment(line)))
			return (st);
		else
			return (st_succ);
	}
	else if (st == st_succ)
		return (st);
	else
		return (g_header_status == 2 ? st_succ : st_error);
}

t_st			parse_line(char **line)
{
	const char		*instr;
	t_st			st;

	if (!line || !*line)
		return (st_error);
	else if ((st = parse_header(*line)) == st_error)
		return (st_error);
	else if (st == st_succ)
		return (st_fail);
	else
	{
		if (is_comment_char(*line[0]))
			return (st_fail);
		instr = *line;
		while (*instr && ft_isspace(*instr))
			instr++;
		if (!*instr)
			return st_fail;
		while (*instr)
		{
			if (is_comment_char(*instr))
			{
				ft_strchange(line, ft_strrdup(*line, instr));
				break;
			}
			else
				instr++;
		}
		return (st_succ);
	}
}


t_hash			g_labels = NULL;
t_champ			g_champ;
int				g_header_status = 0;
t_u8			g_name[PROG_NAME_LENGTH + 1];
