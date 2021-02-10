/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 13:00:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"
#include "color.h"

void				mem_load(t_u8 player_num, t_player *p, const t_champ *champ)
{
	t_u16				i;
	t_u16				j;

	assert(p != NULL);
	j = 0;
	i = (MEM_SIZE / g_vm.nplayers) * player_num;
	p->prog = new_process(player_num, i);
	p->prog->reg[1] = -((t_s8)player_num + 1);
	while (j < champ->prog_size)
	{
		set_color(player_num + 1, i);
		g_vm.arena[i++] = champ->file[j++];
	}
}

void				mem_chunk(t_proc p, t_arg arg, t_u8 *offset)
{
	t_u8 off;

	if (encoded(op_encoding(p, arg)) == T_REG)
	{
		p->op.args.v[arg] = at_mem(shift_pc(p, *offset));
		*offset += 1;
	}
	else
	{
		mem_read_chunk(p, arg, offset);
		if (encoded(op_encoding(p, arg)) == T_IND)
		{
			// short_chunk in case of T_DIR
			// T_IND is sizeof short
			off = p->op.args.c[arg].u16;
			mem_read_chunk(p, arg, &off);
		}
	}
}
