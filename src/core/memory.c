/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/01/23 17:39:19 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

inline t_u8			color_owner(t_u16 at)
{
	assert(at < MEM_SIZE);
	return (g_memcolors[at] & 0x0f);
}

inline t_u8			color_writer(t_u16 at)
{
	assert(at < MEM_SIZE);
	return (~(g_memcolors[at] >> 4) ? 0
				: ((g_memcolors[at] >> 4) + color_count));
}

static inline void	set_mem_color(t_u8 color, t_u16 at)
{
	assert(color < 5 &&  color > 0 && at < MEM_SIZE);
	g_memcolors[at] >>= 4;
	if (!g_memcolors[at])
		g_memcolors[at] = color;
	else if (color_owner(at) != color)
		g_memcolors[at] |= (color << 4);
}

/* implement circular memory */
static inline t_st	mem_write(t_u8 player, t_addr at, t_addr arr, t_u16 size)
{
	if (at - g_arena > MEM_SIZE)
		return (st_fail);
	while (size--)
	{
		set_mem_color(player + 1, at - g_arena);
		*at++ = *arr++;
	}
	return (st_succ);
}

t_st				mem_load(void)
{
    t_addr		front;
    t_u16		step;
    t_player	*player;

    front = g_arena;
    step = (MEM_SIZE / g_nplayers);
    while (g_nplayers--)
	{
        player = g_gladiators + g_nplayers;
        mem_write(g_nplayers, front, player->champ.file,
					player->champ.hdr.prog_size);
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
