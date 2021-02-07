/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/02/07 11:17:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op_impl.h"
#include "builtin.h"
#include "process.h"

static inline bool	vm_decode_exec()
{
	t_u8	instr_offset;

	instr_offset = 0;
	if (vm_decode(proc, &instr_offset))
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, "player %d: `%s` has correct encoding\n", p->num, p->op.name);
		p->op.callback(proc);
		return (true);
	}
	else
	{
		*(t_st *)arg = st_fail;
		ft_dprintf(g_fd, "player %d: skip `%s` incorrect encoding!\n", p->num, p->op.name);
		move_pc(p, instr_offset);
		return (false);
	}  
}

void			vm_exec(void *proc, void *arg)
{
	t_proc	p;

	if ((p = proc)->op.callback == op_nop)
		return ;
	else if (!p->op.cycles)
	{
		if (!vm_decode_exec())
			return ;
		else if (p->op.callback == zjmp)
		{
			*(t_st *)arg = st_succ;
			ft_dprintf(g_fd, "player %d jumped to address: %0#4x\n", p->num, p->pc);
		}
		else
			move_pc(p, instr_offset);
		set_nop(p);
	}
	else
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, "player %d: `%s` operation has more %d cycles to wait\n", p->num, p->op.name, p->op.cycles);
		p->op.cycles++;
	}
}
