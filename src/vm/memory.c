/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 19:42:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "color.h"
#include "process.h"

/* implement circular memory */
static inline t_st	mem_write(t_u8 player, t_u16 at, t_cor arr, t_u16 size)
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
					player->champ.hdr.prog_size);
		player->prog = new_process(iplayer + 1, front);
		set_color(iplayer + 1 + color_count, front);
        front += step;
    }
    return st_succ;
}

t_st			mem_chunk(t_proc p, t_u8 which, t_blob *value)
{
	/* t_args_value		arg; */
	/* t_u16			pc; */

    value->v[which] = 0;

	if (p->op.meta.of.long_op)
		pc = shift_pc(p);

	arg.val.byte_4 = g_vm.arena[pc];
	arg.val.byte_3 = g_vm.arena[pc + 1];

	if (p->op.chunk_size > 2)
	{
		arg.val.byte_2 = g_vm.arena[pc + 2];
		arg.val.byte_1 = g_vm.arena[pc + 3];
	}

	return (arg.value);
}

t_u8				mem_deref(t_proc p, t_u16 offset)
{
	return g_vm.arena[shift_pc(p, offset)];
}
