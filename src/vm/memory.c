/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/02/04 17:51:23 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "color.h"
#include "process.h"

/* implement circular memory */
static inline t_st	mem_write(t_u8 player, t_u16 at, t_u8 arr[], t_u16 size)
{
	if (at > MEM_SIZE)
		return (st_fail);
 	while (size--)
	{
		set_color(player + 1, at);
		g_vm.arena[at++] = *arr++;
	}
	return (st_succ);
}

t_st				mem_load(void)
{
    t_u16		front;
    t_u16		step;
    t_player	*player;
	t_u8		iplayer;

    front = 0;
    step = (MEM_SIZE / g_vm.nplayers);
	iplayer = g_vm.nplayers;
    while (iplayer--)
	{
        player = g_vm.gladiators + iplayer;
        mem_write(iplayer, front, player->champ.file,
					player->champ.prog_size);
		player->prog = new_process(iplayer + 1, front);
		set_color(iplayer + 1 + color_count, front);
        front += step;
    }
    return st_succ;
}

static inline void read_word_size(t_u16 pc, union u_chunk *chunk, bool shrt_chunk, bool long_op)
{
    chunk->val.byte_4 = at_mem(pc);
	chunk->val.byte_3 = pc_shift(pc, 1, long_op);
	if (!shrt_chunk)
	{
	    chunk->val.byte_2 = pc_shift(pc, 2, long_op);
	    chunk->val.byte_1 = pc_shift(pc, 3, long_op);
	}
}

t_st				mem_chunk(t_proc p, t_arg arg)
{
	/* t_args_value		arg; */
	/* t_u16			pc; */

    /* value->v[which] = 0; */

	/* if (p->op.meta.of.long_op) */
	/* 	pc = shift_pc(p); */

	/* arg.val.byte_4 = g_vm.arena[pc]; */
	/* arg.val.byte_3 = g_vm.arena[pc + 1]; */

	/* if (p->op.chunk_size > 2) */
	/* { */
	/* 	arg.val.byte_2 = g_vm.arena[pc + 2]; */
	/* 	arg.val.byte_1 = g_vm.arena[pc + 3]; */
	/* } */

	/* return (arg.value); */

/////////

	if (op_meta_encoding(p, arg) & encoded(op_encoding(p, arg)))
	{

	}
	p->op.args.b[arg].val.byte_4 = mem_at(p);
	p->op.args.b[arg].val.byte_3 = shift_pc(p, 1);
	if (!p->op.meta.of.short_chunk)
	{
		p->op.args.b[arg].val.byte_4 = shift_pc(p, 2);
		p->op.args.b[arg].val.byte_3 = shift_pc(p, 3);
	}
	return (st_succ);
}

t_u8			mem_deref(t_proc p, t_u16 offset)
{
	return g_vm.arena[shift_pc(p, offset)];
}

t_u8			mem_at(t_proc p)
{
	return mem_deref(p, 0);
}

t_u8			at_mem(t_u16 pc)
{
	return g_vm.arena[pc % MEM_SIZE];
}
