/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:50:37 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 17:52:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "memory.h"
#include "draw.h"

void    st(t_proc proc)
{
	union u_chunk	chnk;

	/* print_arena(); */
	if (encoded(op_encoding(proc, 1)) == T_REG)
		proc->reg[proc->op.args.v[1]] = proc->reg[proc->op.args.v[0]];
	else
	{
		chnk.chunk = proc->reg[proc->op.args.v[0]];
		mem_write_chunk(proc, &chnk, arg_value(proc, 1, false));
	}
	/* print_arena(); */
}

void    sti(t_proc proc)
{
	union u_chunk	chnk;
	t_u32			offset;

	/* print_arena(); */
	offset = arg_value(proc, 1, false) + arg_value(proc, 2, false);
	chnk.chunk = proc->reg[proc->op.args.v[0]];
	mem_write_chunk(proc, &chnk, offset);
	/* print_arena(); */
}
