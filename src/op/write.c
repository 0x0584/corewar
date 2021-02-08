/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:50:37 by archid-           #+#    #+#             */
/*   Updated: 2021/02/08 17:40:45 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void    st(t_proc proc)
{
	union u_chunk	chnk;

	if (encoded(op_encoding(proc, 1)) == T_REG)
		proc->reg[proc->op.args.c[0].u32] = proc->reg[proc->op.args.c[1].u32];
	else
	{
		chnk.u32 = proc->reg[proc->op.args.c[0].u32];
		mem_write_chunk(proc->op.args.c[1].u16, &chnk, &proc->op);
	}
}

void    sti(t_proc proc)
{
	union u_chunk chnk;

	chnk.u32 = proc->reg[proc->op.args.v[0]];
	mem_write_chunk(proc->op.args.v[1] + proc->op.args.v[2], &chnk, &proc->op);
}
