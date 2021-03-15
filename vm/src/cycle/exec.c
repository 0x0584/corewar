/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:43:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op_callback.h"

bool			g_jumped = false;

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
		return (st_fail);
	}
}

static t_u8			vm_decode_exec(t_proc proc, t_st *arg)
{
	t_pc				op_arg_offset;
	t_pc				old;
	const char			*bytecode;

	op_arg_offset = 0;
	if (verify_proc(proc, arg))
		return (0);
	else if (vm_decode(proc, &op_arg_offset))
	{
		*(t_st *)arg = st_fail;
		old = proc->pc;
		bytecode = op_bytecode(&proc->op.info);
		move_pc(proc, op_arg_offset);
		ft_dprintf(g_fd, "ADV %hd (0x%04x -> 0x%04x) ",
					proc->pc - old, old, proc->pc);
		while (old < proc->pc)
			ft_dprintf(g_fd, "%02x ", g_vm.arena[old++]);
		ft_putchar_fd('\n', g_fd);
		set_nop(proc);
		return (0);
	}
	else
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, proc->op.callback == zjmp ? "P %4d | " : "P %4d | %s",
					proc->pid, op_disasm(proc));
		proc->op.callback(proc);
		return (op_arg_offset);
	}
}

void				vm_exec(void *proc, void *arg)
{
	t_u8				offset;
	t_proc				p;
	t_pc				old;
	const char			*bytecode;

	g_jumped = false;
	p = proc;
	old = p->pc;
	if (!(offset = vm_decode_exec(proc, arg)))
		return ;
	else if (!g_jumped)
	{
		bytecode = op_bytecode(&p->op.info);
		move_pc(proc, offset);
		ft_dprintf(g_fd, "ADV %hd (0x%04x -> 0x%04x) %s", p->pc - old, old,
					p->pc, bytecode);
	}
	set_nop(proc);
}
