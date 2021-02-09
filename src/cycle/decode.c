/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/08 17:36:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

t_st		vm_decode(t_proc p, t_u8 *offset)
{
	t_st st;

	if (p->op.meta.of.encoded)
	{
		p->op.encoded.encod = at_mem(shift_pc(p, 1));
		ft_dprintf(g_fd, ">	 encoding of %s is %08b %08x\n", p->op.name, p->op.encoded.encod, p->op.encoded.encod);
		st = read_arg_chunk(p, offset);
		*offset += 2;
		ft_dprintf(g_fd, "read %d\n", st);
		return (st);
	}
	else
	{
		mem_read_chunk(shift_pc(p, 1), p->op.args.c, &p->op, offset);
		*offset += 1;		
		return (st_succ);
	}
}
