/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/16 10:33:48 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"
#include "builtin.h"

t_st		vm_decode(t_proc p, t_pc *offset)
{
	t_st st;

	//ft_bzero(&p->op.args, sizeof(t_blob) * MAX_ARGS_NUMBER);
	if (p->op.info.meta.of.encoded)
	{
		p->op.info.encoded.encod = at_mem(shift_pc(p, 1));
		ft_dprintf(g_fd, ">	 encoding of %s is %08b %08x\n", p->op.info.name, p->op.info.encoded.encod, p->op.info.encoded.encod);
		*offset += 2;
		st = read_arg_chunk(p, offset);
		ft_dprintf(g_fd, "read %d\n", st);
		return (st);
	}
	else
	{
		*offset += 1;
		mem_read_chunk(p, &p->op.info.args.c[0], p->op.callback == live, *offset);
		*offset += p->op.callback == live ? REG_SIZE : IND_SIZE;
		return (st_succ);
	}
}
