/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:45:32 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 16:46:13 by archid-          ###   ########.fr       */
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
