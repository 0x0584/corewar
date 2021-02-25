/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/02/25 11:53:30 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool			g_jumped = false;

static t_st			verify_proc(t_proc p, void *arg)
{

	if (!p->op.callback || p->op.callback == nop)
		return (st_error);
    p->op.cycles++;
	if (!p->op.cycles)
		return (st_succ);
	else
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, " >>> player %d: `%s` operation has more %d cycles to wait\n", p->num, p->op.info.name, -p->op.cycles);
		return (st_fail);
	}
}

static t_u8			vm_decode_exec(t_proc proc, t_st *arg)
{
	t_pc				op_arg_offset;

	if (verify_proc(proc, arg))
		return (0);
	else if (vm_decode(proc, &op_arg_offset))
	{
		*(t_st *)arg = st_fail;
		ft_dprintf(g_fd, " >>> player %d: %{red_fg}skip `%s` incorrect encoding!%{reset}\n", proc->num, proc->op.info.name);
		move_pc(proc, op_arg_offset);
		return (0);
	}
	else
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, " >>> player %d: `%s` has correct encoding\n", proc->num, proc->op.info.name);
		op_dump(&proc->op, true, true);
		proc->op.callback(proc);
		if (proc->op.callback == zjmp)
		{
			g_jumped = true;
			ft_dprintf(g_fd, " >>> player %d g_jumped to address: %0#4x\n", proc->num, proc->pc);
		}
		return (op_arg_offset);
	}

}

void				vm_exec(void *proc, void *arg)
{
	t_u8				offset;
	t_proc				p;
	t_pc				old;

	g_jumped = false;
	p = proc;
	if (!(offset = vm_decode_exec(proc, arg)))
		return ;
	else if (!g_jumped)
	{
		old = p->pc;
		move_pc(proc, offset);
		ft_dprintf(g_fd ,"P %-4d: ADV %hd (0x%04x ->0x%04x) | nop\n", p->num, p->pc - old, old, p->pc);
	}
	set_nop(proc);
}
