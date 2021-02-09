/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/02/08 17:47:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

#include "color.h"

void				mem_write_chunk(t_u16 pc, union u_chunk *chnk, const t_op *op)
{
	g_vm.arena[pc_shift(pc, 0, op->meta.of.long_op)] = chnk->val.byte_4;
	g_vm.arena[pc_shift(pc, 1, op->meta.of.long_op)] = chnk->val.byte_3;
	if (op->meta.of.short_chunk)
	{
		g_vm.arena[pc_shift(pc, 2, op->meta.of.long_op)] = chnk->val.byte_2;
		g_vm.arena[pc_shift(pc, 3, op->meta.of.long_op)] = chnk->val.byte_1;
	}
}

void				mem_read_chunk(t_u16 pc, union u_chunk *chnk, const t_op *op, t_u8 *offset)
{
	chnk->val.byte_4 = at_mem(pc_shift(pc, *offset, op->meta.of.long_op));
	chnk->val.byte_3 = at_mem(pc_shift(pc, *offset + 1, op->meta.of.long_op));
	*offset += 2;
	if (!op->meta.of.short_chunk)
	{
		chnk->val.byte_2 = at_mem(pc_shift(pc, *offset, op->meta.of.long_op));
		chnk->val.byte_1 = at_mem(pc_shift(pc, *offset + 1, op->meta.of.long_op));
		*offset += 2;
	}
}

void				mem_chunk(t_proc p, t_arg arg, t_u8 *offset)
{
	union u_chunk		c;
	t_u8				off;

	if (encoded(op_encoding(p, arg)) == T_REG)
	{
		p->op.args.v[arg] = at_mem(shift_pc(p, *offset));
		*offset += 1;
	}
	else
	{
		c.u32 = 0;
		off = 0;
		mem_read_chunk(p->pc, &c, &p->op, offset);
		if (encoded(op_encoding(p, arg)) == T_IND)
			mem_read_chunk(c.u16, &p->op.args.c[arg], &p->op, &off);
		else
			p->op.args.c[arg] = c;
	}
}

void				mem_load(t_u8 player_num, t_player *p, const t_champ *champ)
{
	t_u16				i;
	t_u16				j;

	assert(p != NULL);
	j = 0;
	i = (MEM_SIZE / g_vm.nplayers) * player_num;
	p->prog = new_process(player_num, i);
	*p->prog->reg = -((t_s8)player_num + 1);
	while (j < champ->prog_size)
	{
		set_color(player_num + 1, i);
		g_vm.arena[i++] = champ->file[j++];
	}
}

t_u8				mem_deref(t_proc p, t_u16 offset)
{
	return g_vm.arena[shift_pc(p, offset)];
}

t_u8				mem_at(t_proc p)
{
	return mem_deref(p, 0);
}

t_u8				at_mem(t_u16 pc)
{
	return g_vm.arena[pc % MEM_SIZE];
}
