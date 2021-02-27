/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:23:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/24 16:21:17 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static char				op_str[MAX_OP_NAME + 1];

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

/**
** \brief parse operation
**
** \param op operation to parse
** \param line line read from file
**
** \return
**
**   - `st_error` if no arguments are found in the same line or operation is unknown
**   - `st_fail` if line containes no instruction
**   - `st_succ` if arguments are fetched correctly
**
** \see fetch_op_args()
*/
t_st					parse_op(t_op *op, const char *line)
{
	const char				*walk;
	t_pair					op_fetcher;

	skip_whitespace(&line);
	if (!*line)
	{
		ft_dprintf(2, "%{yellow_fg}>> empty line%{reset}\n");
		return st_fail;
	}

	walk = line;
	while (*walk && ft_isalpha(*walk) && walk - line < MAX_OP_NAME)
		walk++;

	if (!ft_isspace(*walk))
	{
		ft_dprintf(2, "%{red_fg}no arguments are found%{reset}\n");
		return st_error;
	}

	ft_bzero(op_str, MAX_OP_NAME + 1);
	ft_strncpy(op_str, line, min(walk - line, MAX_OP_NAME));
	op_fetcher = (t_pair){NULL, op};
	hash_iter_arg(g_op_lookup, &op_fetcher, find_op);
	if (op_fetcher.first)
		return (fetch_op_args(op, walk));
	else
	{
		ft_dprintf(2, "%{red_fg}unknown operation `%s`%{reset}\n", op_str);
		return (st_error);
	}
}

/**
** \brief parse label if found
**
** \param line read from the file
** \param op_start out reference after reading the label successfully
** \param op to be bound with the label
**
** \return
**
**   - `st_error` if label is duplicted or containes illegal characters
**   - `st_fail` if no label is found or empty label
**   - `st_succ` otherwise
*/
static t_st		parse_label(const char *line, const char **op_start, const t_op *op)
{
	const char	*walk;
	char		*label;
	t_st		st;

	skip_whitespace(&line);
	if (*line == LABEL_CHAR)
	{
		ft_dprintf(2, "%{red_fg}empty label is illegal%{reset}\n");
		return (st_error);
	}

	walk = line;
	while (*walk && !(*walk == LABEL_CHAR || delimiter(*walk)))
		walk++;

	if (!*walk)
	{
		ft_dprintf(2, "%{yellow_fg}end of line%{reset}\n");
		*op_start = line;
		return st_fail;
	}
	else if (*walk != LABEL_CHAR)
	{
		ft_dprintf(2, "%{yellow_fg}not label%{reset}\n");
		*op_start = line;
		return st_fail;
	}

	if (valid_label(label = ft_strrdup(line, walk - 1)))
		return st_error;
	else if (!hash_add(g_labels, label, op))
	{
		ft_dprintf(2, "%{red_fg}duplicated label%{reset}\n");
		st = st_error;
	}
	else
	{
		st = st_succ;
		*op_start = ++walk;
	}

	free(label);
	return (st);
}

static void		delete_ops(t_op *op, t_lst *ops)
{
	lst_del(ops);
	free(op);
}

void			print_op(void *blob)
{
	t_op *op = blob;

	ft_printf("name: %s\n", op->info.name);
}

t_lst			parse_ops(t_lst lines)
{
	t_lst			ops;
	t_lstnode		walk;
	t_op			*op;
	const char		*op_at;
	t_st			st;

	bool			op_on_hold;

	ops = lst_alloc(blob_free);
	walk = lst_front(lines);

	op_on_hold = true;

	while (walk)
	{
		if (op_on_hold)
		{
			op = ft_calloc(1, sizeof(t_op));
			op_on_hold = false;
		}

		if (parse_label(walk->blob, &op_at, op) == st_error
			|| (st = parse_op(op, op_at)) == st_error)
		{
			delete_ops(op, &ops);
			break;
		}
		else if (st == st_succ)
		{
			lst_push_back_blob(ops, op, sizeof(t_op), false);
			op_on_hold = true;
		}
		lst_node_forward(&walk);
	}
	lst_iter(ops, true, print_op);
	return ops;
}
