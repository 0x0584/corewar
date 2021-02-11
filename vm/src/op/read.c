/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:40:20 by archid-           #+#    #+#             */
/*   Updated: 2021/02/11 17:57:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "memory.h"
#include "draw.h"

void	ld(t_proc proc)
{
	print_arena();
	if (!(proc->reg[proc->op.args.v[1]] = arg_value(proc, 0, true)))
		proc->carry = true;
	print_arena();
}

void	lld(t_proc proc)
{
	ld(proc);
}

void	ldi(t_proc proc)
{
	t_u32			offset;
	union u_chunk	chnk;

	offset = arg_value(proc, 0, true) + arg_value(proc, 1, false);
	mem_read_chunk(proc, &chnk, true, offset);
	proc->reg[proc->op.args.v[2]] = chnk.u32;
}

void	lldi(t_proc proc)
{
	ldi(proc);
}
