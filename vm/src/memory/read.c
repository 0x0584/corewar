/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:52:26 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 10:09:44 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"

void				mem_read_chunk(const t_proc p, union u_chunk *chnk,
										bool read_reg_size, t_pc offset)
{
	chnk->chunk = 0;
	if (read_reg_size)
	{
		chnk->val.byte_4 = at_mem(pc_shift(p->pc, offset,
									p->op.info.meta.of.long_op));
		chnk->val.byte_3 = at_mem(pc_shift(p->pc, offset + 1,
									p->op.info.meta.of.long_op));
		chnk->val.byte_2 = at_mem(pc_shift(p->pc, offset + 2,
									p->op.info.meta.of.long_op));
		chnk->val.byte_1 = at_mem(pc_shift(p->pc, offset + 3,
									p->op.info.meta.of.long_op));
	}
	else
	{
		chnk->val.byte_2 = at_mem(pc_shift(p->pc, offset,
									p->op.info.meta.of.long_op));
		chnk->val.byte_1 = at_mem(pc_shift(p->pc, offset + 1,
									p->op.info.meta.of.long_op));
	}
}
