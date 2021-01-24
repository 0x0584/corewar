/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/01/24 16:50:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "color.h"

/* implement circular memory */
static inline t_st	mem_write(t_u8 player, t_addr at, t_addr arr, t_u16 size)
{
	if (at - g_arena > MEM_SIZE)
		return (st_fail);
 	while (size--)
	{
		set_color(player + 1, at - g_arena);
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

    front = g_arena;
    step = (MEM_SIZE / g_nplayers);
	iplayer = g_nplayers;
    while (iplayer--)
	{
        player = g_gladiators + iplayer;
        mem_write(iplayer, front, player->champ.file,
					player->champ.hdr.prog_size);
		player->prog = new_process(iplayer, front, false);
		set_color(iplayer + 1 + color_count, front - g_arena);
        front += step;
    }
    return st_succ;
}

/*
** Global Variables
*/
t_memory			g_arena;
t_players			g_gladiators;
t_u8				g_memcolors[MEM_SIZE];
