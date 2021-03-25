/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:23:56 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 16:46:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static t_st		parse_label(const char *line, const char **op_start,
								const t_op *op)
{
	const char	*walk;
	char		*label;
	t_st		st;

	if (*line == LABEL_CHAR)
		return (st_log(st_error, 2, "empty label is illegal"));
	else if (!*line)
		return (st_fail);
	walk = line;
	while (*walk && !(*walk == LABEL_CHAR || delimiter(*walk)))
		walk++;
	if (!*walk)
		return (st_log(st_error, 2, "invalid label syntax"));
	else if (*walk != LABEL_CHAR)
		return (st_fail);
	else if (valid_label(label = ft_strrdup(line, walk - 1)) ||
				!hash_add(g_labels, label, op))
		st = st_log(st_error, 2, "duplicated label %s", label);
	else
	{
		st = st_succ;
		*op_start = ++walk;
	}
	free(label);
	return (st);
}

static bool		parse_asm(t_op **op, const char **op_at,
								t_st *st_op, t_lst ops)
{
	t_st	st_label;

	if ((st_label = parse_label(*op_at, op_at, *op)) == st_error ||
		(*st_op = parse_op(*op, *op_at, st_label)) == st_error)
	{
		op_free(*op);
		return (false);
	}
	else if (*st_op == st_succ)
	{
		lst_push_back_blob(ops, *op, sizeof(t_op), false);
		*op = NULL;
	}
	return (true);
}

static bool		do_parse_ops(t_lstnode walk, t_lst ops)
{
	t_op			*op;
	const char		*op_at;
	t_st			st_op;

	op = NULL;
	while (walk)
	{
		if (!op)
			op = ft_calloc(1, sizeof(t_op));
		op_at = walk->blob;
		st_op = st_fail;
		skip_whitespace(&op_at);
		if (*op_at)
			if (!parse_asm(&op, &op_at, &st_op, ops))
				return (false);
		lst_node_forward(&walk);
	}
	if (!*op_at && st_op == st_fail)
	{
		st_log(st_error, 2, "last label points to nothing");
		op_free(op);
		return (false);
	}
	return (true);
}

t_lst			parse_ops(t_lst lines)
{
	t_lstnode	walk;
	t_lst		ops;

	if (lst_empty(lines))
		return (NULL);
	ops = lst_alloc(op_free);
	walk = lst_front(lines);
	if (!do_parse_ops(walk, ops))
		lst_del(&ops);
	return (ops);
}
