/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:52:22 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 17:51:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"

/**
 * \brief write operation arg into arena at pc relative to offset
 *
 * st/sti are the only operation to set memory both set the value of REG_SIZE
 */
void				mem_write_chunk(const t_proc p, const union u_chunk *chnk, t_pc offset)
{
	/* print_arena(); */
	g_vm.arena[pc_shift(p->pc, offset, p->op.info.meta.of.long_op)] = chnk->val.byte_4;
	g_vm.arena[pc_shift(p->pc, offset + 1, p->op.info.meta.of.long_op)] = chnk->val.byte_3;
	g_vm.arena[pc_shift(p->pc, offset + 2, p->op.info.meta.of.long_op)] = chnk->val.byte_2;
	g_vm.arena[pc_shift(p->pc, offset + 3, p->op.info.meta.of.long_op)] = chnk->val.byte_1;
	/* print_arena(); */
}
