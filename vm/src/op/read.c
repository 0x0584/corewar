/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:40:20 by archid-           #+#    #+#             */
/*   Updated: 2021/03/13 17:07:20 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "op_callback.h"

#include "draw.h"

void	ld(t_proc proc)
{
	/* print_arena(); */
	proc->carry = !(proc->reg[proc->op.info.args.v[1]] = arg_value(proc, 0, true));
	/* print_arena(); */
}

void	lld(t_proc proc)
{
	ld(proc);
}

void	ldi(t_proc proc)
{
	t_u32			offset;
	t_ind			lval;
	t_ind			rval;
	union u_chunk	chnk;

	lval = arg_value(proc, 0, true);
	rval = arg_value(proc, 1, false);
	offset = lval + rval;
	mem_read_chunk(proc, &chnk, true, offset);
	proc->reg[proc->op.info.args.v[2]] = chnk.chunk;
	if (proc->op.info.code == op_lldi)
		proc->carry = !proc->reg[proc->op.info.args.v[2]];
	ft_dprintf(g_fd, "%8s -> load from %hd + %hd = %hd (with pc and mod %hd)\n", "|",
			   lval, rval, offset, shift_pc(proc, offset));

}

void	lldi(t_proc proc)
{
	ldi(proc);
}
