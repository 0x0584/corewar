/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:23:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 16:36:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "op_impl.h"

static char				op_str[MAX_OP_NAME];

static void				find_op(const char *key, void *blob, void *arg)
{
	if (((t_pair *)arg)->first)
		return ;
	else if (!ft_strncmp(key, op_str, MAX_OP_NAME))
	{
		ft_memcpy((void *)&((t_op *)(((t_pair *)arg)->second))->info,
				  blob, sizeof(t_op_info));
		((t_pair *)arg)->first = ((t_pair *)arg)->second;
	}
}

t_st					parse_op(t_op *op, const char *buff)
{
	const char				*spc;
	t_pair					op_fetcher;

	skip_whitespace(&buff);
	if (!*buff)
	{
		ft_dprintf(2, " >> empty line\n");
		return st_fail;
	}
	else if (!(spc = ft_strchr(buff, ' ')))
	{
		ft_dprintf(2, "no arguments are found\n");
		return st_error;
	}

	ft_bzero(op_str, 5);
	ft_strncpy(op_str, buff, min(spc - buff - 1, 4));
	op_fetcher = (t_pair){NULL, op};
	hash_iter_arg(g_op_lookup, &op_fetcher, find_op);
	if (op_fetcher.first)
		return (fetch_op_args(op, spc));
	else
	{
		ft_dprintf(2, "unknow operation `%s`\n", op_str);
		return (st_error);
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
