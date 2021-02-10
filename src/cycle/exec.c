/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/02/09 15:58:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool			g_jumped = false;

static t_st			verify_proc(t_proc p, void *arg)
{

	if (p->op.callback == op_nop)
		return (st_error);
    p->op.cycles++;
	if (!p->op.cycles)
		return (st_succ);
	else
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, "player %d: `%s` operation has more %d cycles to wait\n", p->num, p->op.name, -p->op.cycles);
		return (st_fail);
	}
}

static t_u8			vm_decode_exec(t_proc proc, t_st *arg)
{
	t_u8				op_arg_offset;

	if (verify_proc(proc, arg))
		return (0);
	else if (vm_decode(proc, &op_arg_offset))
	{
		*(t_st *)arg = st_fail;
		ft_dprintf(g_fd, ">> player %d: skip `%s` incorrect encoding!\n", proc->num, proc->op.name);
		move_pc(proc, op_arg_offset);
		return (0);
	}
	else
	{
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, ">> player %d: `%s` has correct encoding\n", proc->num, proc->op.name);
		proc->op.callback(proc);
		if (proc->op.callback == zjmp)
		{
			g_jumped = true;
			ft_dprintf(g_fd, ">> player %d g_jumped to address: %0#4x\n", proc->num, proc->pc);
		}
		return (op_arg_offset);
	}

}

void				vm_exec(void *proc, void *arg)
{
	t_u8				offset;

	g_jumped = false;
	if (!(offset = vm_decode_exec(proc, arg)))
		return ;
	else if (!g_jumped)
		move_pc(proc, offset);
}