/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:22:26 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 17:46:05 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

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

static t_st		parse_header(const char *line)
{
	const char		*walk;
	t_st			st;

	walk = line;
	st = st_fail;
	while (*walk && ft_isspace(*walk))
		walk++;
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

static t_st		parse_label(const char *line, const char **op_start, const t_op *op)
{
	const char	*tmp;
	const char	*walk;
	char		*label;
	t_st		st;

	if (*line == LABEL_CHAR)
	{
		ft_dprintf(2, "empty label is illegal\n");
		return st_error;
	}
	if (!(tmp = ft_strchr(line, LABEL_CHAR)))
		return st_fail;
	walk = line;
	while (walk != tmp)
	{
		if (!ft_strchr(LABEL_CHARS, *walk))
		{
			ft_dprintf(2, "label contains illigale characters\n");
			return st_error;
		}
		walk++;
	}
	if (!hash_add(g_labels, label = ft_strrdup(line, tmp - 1), op))
	{
		ft_dprintf(2, "duplicated label\n");
		st = st_error;
	}
	else
	{
		st = st_succ;
		*op_start = walk;
	}
	free(label);
	return st;
}

t_lst			parse_ops(t_lst lines)
{
	t_lst			ops;
	t_lstnode		walk;
	t_op			*op;
	const char		*op_at;

	t_st			st;

	ops = lst_alloc(blob_free);
	walk = lst_front(lines);
	while (walk)
	{
		if (parse_label(walk->blob, &op_at, op = ft_calloc(1, sizeof(t_op))) == st_error ||
			(st = parse_op(op, op_at)) == st_error)
		{
			lst_del(&ops);
			break;
		}
		else if (st == st_succ)
			lst_push_back_blob(ops, op, sizeof(t_op), false);
		lst_node_forward(&walk);
	}
	return ops;
}

t_st		parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{

}

t_hash			g_labels = NULL;
t_champ			g_champ;
int				g_header_status = 0;
t_u8			g_name[PROG_NAME_LENGTH + 1];
