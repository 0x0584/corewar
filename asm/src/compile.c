/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:25:02 by archid-           #+#    #+#             */
/*   Updated: 2021/02/19 16:13:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static int i = 0;

static void		dump_line(void *blob)
{
	ft_printf(" line %d `%s`\n", i++, blob);
}

t_st			compile(t_lst lines, const char *outname)
{
	t_lst			ops;
	t_st			st;

	lst_iter(lines, true, dump_line);
	if ((ops = parse_ops(lines)))
	{
		st = write_prog(ops, outname);
		lst_del(&ops);
		return st;
	}
	else
	{
		return st_error;
	}
}
