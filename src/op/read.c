/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:40:20 by archid-           #+#    #+#             */
/*   Updated: 2021/02/08 15:04:49 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ld(t_proc proc)
{
	proc->reg[proc->op.args.v[1]] = proc->op.args.v[0];
}

void	ldi(t_proc proc)
{
	t_u32			addr;
	union u_chunk	chnk;

	addr = get_arg_value(proc, 0) + get_arg_value(proc, 1);
	mem_read_chunk(addr, &chnk, &proc->op, 0);
	proc->reg[proc->reg[proc->op.args.v[2]]] = chnk.u32;
}

void	lld(t_proc proc)
{
	ld(proc);
}

void	lldi(t_proc proc)
{
	ldi(proc);
}
