/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:41:34 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 15:44:41 by archid-          ###   ########.fr       */
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

void				mem_chunk(t_proc p, t_arg arg, t_u16 *offset)
{
	bool read_reg_size;

	if (encoded(op_encoding(p, arg)) == T_REG)
	{
		p->op.args.v[arg] = at_mem(shift_pc(p, *offset));
		*offset += 1;
	}
	else
	{
		read_reg_size = !p->op.meta.of.short_chunk && encoded(op_encoding(p, arg)) == T_DIR;
		mem_read_chunk(p, &p->op.args.c[arg], read_reg_size, *offset);
		op_dump(&p->op, true, false);
		if (encoded(op_encoding(p, arg)) == T_IND)
		{
			ft_dprintf(g_fd, " ## indirect arg \n");
			mem_read_chunk(p, &p->op.args.c[arg], true, p->op.args.c[arg].u16);
			op_dump(&p->op, true, false);
			*offset += IND_SIZE;
		}
		else
			*offset += read_reg_size ? DIR_SIZE : IND_SIZE;
	}
}
