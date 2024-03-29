/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:50:37 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 18:47:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "op_callback.h"

void		st(t_proc proc)
{
	union u_chunk	chnk;

	if (decode(op_encoding(&proc->op.info, 1)) == T_REG)
		proc->reg[proc->op.info.args.v[1]] = proc->reg[proc->op.info.args.v[0]];
	else
	{
		chnk.chunk = proc->reg[proc->op.info.args.v[0]];
		mem_write_chunk(proc, &chnk, arg_value(proc, 1, false));
	}
}

void		sti(t_proc proc)
{
	union u_chunk	chnk;
	t_u32			offset;
	t_ind			lval;
	t_ind			rval;

	lval = arg_value(proc, 1, false);
	rval = arg_value(proc, 2, false);
	offset = lval + rval;
	chnk.chunk = proc->reg[proc->op.info.args.v[0]];
	mem_write_chunk(proc, &chnk, offset);
	if (g_verbose & show_ops)
		ft_dprintf(g_fd,
					"%8s -> store to %hd + %hd = %hd (with pc and mod %hd)\n",
					"|", lval, rval, offset, shift_pc(proc, offset));
}
