/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:59:25 by archid-           #+#    #+#             */
/*   Updated: 2021/02/26 10:08:39 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static void		ops_init(void)
{
	t_op_code		op;

	g_op_lookup = hash_alloc(op_count, blob_keep);
	g_labels = hash_alloc(op_count, blob_keep);
	op = op_nop;
	while (op < op_count)
	{
		hash_add(g_op_lookup, g_ops[op].name, g_ops + op);
		g_max_op_length = umax(g_max_op_length, ft_strlen(g_ops[op++].name));
	}
}

static void		ops_del(void)
{
	hash_del(&g_op_lookup);
	hash_del(&g_labels);
}

int				main(int ac, const char *av[])
{
	t_st			st;

	ops_init();
	st = read_file(ac, av);
	ops_del();
	return (st);
}

t_hash			g_op_lookup = NULL;
t_u16			g_max_op_length = 0;
