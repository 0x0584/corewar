/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 17:30:32 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op_impl.h"

void	vm_exec(void *proc)
{
	t_proc	p;
	t_u8	instr_offset;

	if (!(p = proc)->op)
		return ;
	else if (!p->cycles_to_wait)
	{
		instr_offset = 0;
		if (vm_decode(proc, &instr_offset))
		{
			ft_dprintf(2, "player %d: `%s` has correct encoding\n", p->num, p->op->op_name);
			ft_dprintf(2, "  arguments: arg1:%08x arg2:%08x arg3:%08x\n",
					   g_args[0], g_args[1], g_args[2]);
			p->op->callback(proc);
		}
		else
		{
			ft_dprintf(2, "player %d: skip `%s` incorrect encoding!\n",
					   p->num, p->op->op_name);
		}
		// zjmp doesnt move the PC
		move_pc(&p->pc, instr_offset);
		p->op = NULL;
	}
	else
	{
		p->cycles_to_wait--;
		ft_dprintf(2, "player %d: `%s` operation has more %d cycles to wait\n",
				   p->num,
				   p->op->op_name, p->cycles_to_wait);
	}
}
