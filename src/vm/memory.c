/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/01/27 12:25:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "color.h"

/* implement circular memory */
static inline t_st	mem_write(t_u8 player, t_addr at, t_addr arr, t_u16 size)
{
	if (at - g_vm.arena > MEM_SIZE)
		return (st_fail);
 	while (size--)
	{
		set_color(player + 1, at - g_vm.arena);
		*at++ = *arr++;
	}
	return (st_succ);
}

t_st				mem_load(void)
{
    t_addr		front;
    t_u16		step;
    t_player	*player;
	t_u8		iplayer;

    front = g_vm.arena;
    step = (MEM_SIZE / g_vm.nplayers);
	iplayer = g_vm.nplayers;
    while (iplayer--)
	{
        player = g_vm.gladiators + iplayer;
        mem_write(iplayer, front, player->champ.file,
					player->champ.hdr.prog_size);
		player->prog = new_process(iplayer + 1, front, false);
		set_color(iplayer + 1 + color_count, front - g_vm.arena);
        front += step;
    }
    return st_succ;
}
