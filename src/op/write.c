/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:50:37 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 10:38:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "draw.h"

void    st(t_proc proc)
{
	union u_chunk	chnk;

	print_arena();
	if (encoded(op_encoding(proc, 1)) == T_REG)
		proc->reg[proc->op.args.c[0].u32] = proc->reg[proc->op.args.c[1].u32];
	else
	{
		chnk.u32 = proc->reg[proc->op.args.c[0].u32];
		mem_write_chunk(shift_pc(proc, proc->op.args.c[1].u16), &chnk, &proc->op);
	}
	print_arena();
}

void    sti(t_proc proc)
{
	union u_chunk	chnk;
	t_u32			addr;

    //draw_memory(draw_loop);
	addr = get_arg_value(proc, 1) + get_arg_value(proc, 2);
	chnk.u32 = proc->reg[proc->op.args.v[0]];
	mem_write_chunk(shift_pc(proc, addr), &chnk, &proc->op);
    //draw_memory(draw_loop);
}
