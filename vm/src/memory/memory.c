/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 22:31:38 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "memory.h"
#include "process.h"

void				mem_load(t_u8 player_idx, const t_champ *champ)
{
	t_u16				i;
	t_u16				j;
	t_proc				proc;

	j = 0;
	i = (MEM_SIZE / g_n_players) * player_idx;
	proc = new_process(player_idx + 1, i);
	proc->reg[1] = -(int)(player_idx + 1);
	while (j < champ->prog_size)
		g_vm.arena[i++] = champ->file[j++];
}

void				mem_chunk(t_proc p, t_arg arg, t_pc *offset)
{
	bool				read_reg_size;

	if (decode(op_encoding(&p->op.info, arg)) == T_REG)
	{
		p->op.info.args.v[arg] = at_mem(shift_pc(p, *offset));
		*offset += 1;
	}
	else
	{
		read_reg_size = !p->op.info.meta.of.short_chunk &&
							(decode(op_encoding(&p->op.info, arg)) == T_DIR);
		mem_read_chunk(p, &p->op.info.args.c[arg], read_reg_size, *offset);
		if (decode(op_encoding(&p->op.info, arg)) == T_IND)
			*offset += IND_SIZE;
		else
			*offset += read_reg_size ? DIR_SIZE : IND_SIZE;
	}
}
