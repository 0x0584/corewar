/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:40:20 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 13:02:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "draw.h"

void	ld(t_proc proc)
{
	//draw_memory(draw_loop);
	print_arena();
	if (!(proc->reg[proc->op.args.v[1]] = proc->op.args.v[0]))
		proc->carry = true;
	print_arena();
	//draw_memory(draw_loop);
}

void	lld(t_proc proc)
{
	ld(proc);
}

void	ldi(t_proc proc)
{
	t_u32			addr;
	union u_chunk	chnk;

	addr = get_arg_value(proc, 0) + get_arg_value(proc, 1);
//	mem_read_chunk(shift_pc(proc, addr), &chnk, &proc->op, 0);
	proc->reg[proc->reg[proc->op.args.v[2]]] = chnk.u32;
}

void	lldi(t_proc proc)
{
	ldi(proc);
}
