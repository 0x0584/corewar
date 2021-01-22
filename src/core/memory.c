/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 15:52:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		mem_load(void)
{
    t_addr		front;
    t_addr		walk;
	t_u16		step;
	t_player	*player;

	front = g_arena;
	step = (MEM_SIZE / g_nplayers);
	while (g_nplayers--)
	{
		walk = front;
		player = g_gladiators + g_nplayers;
		while (walk - front < player->hdr.prog_size)
		{
			*walk = g_gladiators->file[walk - front];
			walk++;
		}
		front += step;
	}
}

/*
** Global Variables Defined in vm.h
*/
t_memory	g_arena;
t_players	g_gladiators;
