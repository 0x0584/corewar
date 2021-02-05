/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/02/05 18:33:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op_impl.h"
#include "builtin.h"
#include "process.h"

void	vm_exec(void *proc, void *arg)
{
	t_proc	p;
	t_u8	instr_offset;

	if ((p = proc)->op.callback == op_nop)
		return ;
	else if (!p->op.cycles)
	{
		instr_offset = 0;

		if (vm_decode(proc, &instr_offset))
		{
			*(t_st *)arg = LOGGER(st_succ, "player %d: `%s` has correct encoding\n", p->num, p->op.name);
		    p->op.callback(proc);
		}
		else
		{
			*(t_st *)arg = LOGGER(st_fail, "player %d: skip `%s` incorrect encoding!\n",
					   p->num, p->op.name);
			move_pc(p, instr_offset);
			return ;
		}

		if (p->op.callback == zjmp)
			*(t_st *)arg = LOGGER(st_succ, "player %d jumped to address: %0#4x\n", p->num, p->pc);
		else
			move_pc(p, instr_offset);
		set_nop(p);
	}
	else
	{
		*(t_st *)arg = LOGGER(st_succ, "player %d: `%s` operation has more %d cycles to wait\n",
							  p->num, p->op.name, p->op.cycles);
		p->op.cycles++;
	}
}
