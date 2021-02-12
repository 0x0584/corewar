/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/12 11:09:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"

t_st		vm_decode(t_proc p, t_pc *offset)
{
	t_st st;

	//ft_bzero(&p->op.args, sizeof(t_blob) * MAX_ARGS_NUMBER);
	if (p->op.meta.of.encoded)
	{
		p->op.encoded.encod = at_mem(shift_pc(p, 1));
		ft_dprintf(g_fd, ">	 encoding of %s is %08b %08x\n", p->op.name, p->op.encoded.encod, p->op.encoded.encod);
		*offset += 2;
		st = read_arg_chunk(p, offset);
		ft_dprintf(g_fd, "read %d\n", st);
		return (st);
	}
	else
	{
		*offset += 1;
		mem_read_chunk(p, &p->op.args.c[0], false, *offset);
		return (st_succ);
	}
}
