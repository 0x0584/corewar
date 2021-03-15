/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:23:56 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:49:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static char				g_op_str[MAX_OP_NAME + 1];

static void		find_op(const char *key, void *blob, void *arg)
{
	if (((t_pair *)arg)->first)
		return ;
	else if (!ft_strncmp(key, g_op_str, MAX_OP_NAME))
	{
		ft_memcpy((void *)&((t_op *)(((t_pair *)arg)->second))->info,
					blob, sizeof(t_op_info));
		((t_pair *)arg)->first = ((t_pair *)arg)->second;
	}
}

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

t_st			parse_op(t_op *op, const char *line, t_st label)
{
	const char				*walk;
	t_pair					op_fetcher;

	skip_whitespace(&line);
	if (!*line)
		return (label == st_fail ? st_error : st_fail);
	walk = line;
	while (*walk && ft_isalpha(*walk) && walk - line < MAX_OP_NAME)
		walk++;
	if (!*walk)
		return (st_fail);
	else if (!ft_isspace(*walk))
		return (st_log(st_error, 2, "no arguments are found"));
	ft_bzero(g_op_str, MAX_OP_NAME + 1);
	ft_strncpy(g_op_str, line, min(walk - line, MAX_OP_NAME));
	op_fetcher = (t_pair){NULL, op};
	hash_iter_arg(g_op_lookup, &op_fetcher, find_op);
	if (op_fetcher.first)
		return (fetch_op_args(op, walk));
	else
		return (st_log(st_error, 2, "unknown operation `%s`", g_op_str));
}

void			op_free(void *blob)
{
	t_op			*op;
	t_arg			arg;

	arg = 0;
	op = blob;
	if (!op)
		return ;
	while (arg < op->info.nargs)
	{
		if (op->labels[arg])
			free((char *)op->labels[arg]);
		arg++;
	}
	free(op);
}

t_lst			parse_ops(t_lst lines)
{
	t_lst			ops;
	t_lstnode		walk;
	t_op			*op;
	const char		*op_at;
	t_st			st_op;
	t_st			st_label;

	if (lst_empty(lines))
		return (NULL);
	ops = lst_alloc(op_free);
	walk = lst_front(lines);
	op = NULL;
	while (walk)
	{
		if (!op)
			op = ft_calloc(1, sizeof(t_op));
		op_at = walk->blob;
		st_op = st_fail;
		st_label = st_fail;
		skip_whitespace(&op_at);
		if (*op_at)
		{
			if ((st_label = parse_label(op_at, &op_at, op)) == st_error ||
				(st_op = parse_op(op, op_at, st_label)) == st_error)
			{
				lst_del(&ops);
				op_free(op);
				break ;
			}
			else if (st_op == st_succ)
			{
				lst_push_back_blob(ops, op, sizeof(t_op), false);
				op = NULL;
			}
		}
		lst_node_forward(&walk);
	}
	if (!*op_at && st_op == st_fail)
	{
		st_log(st_error, 2, "last label points to nothing");
		lst_del(&ops);
		op_free(op);
	}
	return (ops);
}
