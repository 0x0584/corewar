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
t_st					parse_op(t_op *op, const char *line, t_st label)
{
	const char				*walk;
	t_pair					op_fetcher;

	skip_whitespace(&line);
	if (!*line)
	{
		if (g_debug)
			ft_dprintf(2, "%{yellow_fg}>> empty line%{reset}\n");
		return label == st_fail ? st_error :  st_fail ;
	}

	walk = line;
	while (*walk && ft_isalpha(*walk) && walk - line < MAX_OP_NAME)
		walk++;

	if (!*walk)
	{
		if (g_debug)
			ft_dprintf(2, "%{yellow_fg}>> empty line%{reset}\n");
		return st_fail;
	}
	else if (!ft_isspace(*walk))
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
	else if (!*line)
	{
		if (g_debug)
			ft_dprintf(2, "%{yellow_fg}empty line%{reset}\n");
		return (st_fail);
	}

	walk = line;
	while (*walk && !(*walk == LABEL_CHAR || delimiter(*walk)))
		walk++;

	if (!*walk)
	{
		ft_dprintf(2, "%{red_fg}invalid label%{reset}\n");
		return st_error;
	}
	else if (*walk != LABEL_CHAR)
	{
		if (g_debug)
			ft_dprintf(2, "%{yellow_fg}not label%{reset}\n");
		*op_start = line;
		return st_fail;
	}

	if (valid_label(label = ft_strrdup(line, walk - 1)))
	{
		free(label);
		return st_error;
	}
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

void			print_op(void *blob)
{
	t_op *op = blob;

	ft_printf("name: %s\n", op->info.name);
}

void op_free(void *blob)
{
	t_op *op;
	t_arg arg;

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
		return NULL;
	ops = lst_alloc(op_free);
	walk = lst_front(lines);
	op = NULL;
	while (walk)
	{
		if (g_debug)
			ft_dprintf(2, "line: `%s`\n", walk->blob);
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
				break;
			}
			else if (st_op == st_succ)
			{
				lst_push_back_blob(ops, op, sizeof(t_op), false);
				op = NULL;
			}
		}
		lst_node_forward(&walk);
	}
	if (g_debug)
		lst_iter(ops, true, print_op);
	if (!*op_at && st_op == st_fail)
	{
		ft_dprintf(2, "%{red_fg}last label points to nothing%{reset}\n");
		lst_del(&ops);
		op_free(op);
	}
	return ops;
}
