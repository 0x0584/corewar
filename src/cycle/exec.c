/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:14 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 15:36:05 by archid-          ###   ########.fr       */
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

void				op_dump(const t_op *op, bool dump_args, bool dump_verbose)
{
	t_arg arg;
	
	ft_dprintf(g_fd, " ### op `%s`:\n %u", op->name, op->nargs);
	ft_dprintf(g_fd, "   encoding : %02x %08b ", op->encoded.encod, op->encoded.encod);
	ft_dprintf(g_fd, "   expecting arg1: %04b, arg2: %04b, arg3: %04b\n",
			   op->meta.of.arg1_t, op->meta.of.arg2_t, op->meta.of.arg3_t);
	if (dump_verbose)
	{
		ft_dprintf(g_fd, "   %s %s sizeof %s %s\n\n",
				   op->meta.of.long_op ? "long" : "idx_mod",
				   op->meta.of.encoded ? "encoded" : "not encoded",
				   op->meta.of.short_chunk ? "short" : "int",
				   op->meta.of.carry ? "has carry" : "");
	}
	if (dump_args)
	{
		arg = 0;
		while (arg < op->nargs)
		{
			ft_dprintf(g_fd, "    arg %u: short(%u) int(%u) %08x: %02x%02x %02x%02x\n", arg,
					   op->args.c[arg].u16,
					   op->args.c[arg].u32,
					   op->args.c[arg].u32,

					   op->args.c[arg].val.byte_1, op->args.c[arg].val.byte_2,
					   op->args.c[arg].val.byte_3, op->args.c[arg].val.byte_4				   
				);
			arg++;
		}
	}
	ft_dprintf(g_fd, " ###\n");   	
}

static t_u8			vm_decode_exec(t_proc proc, t_st *arg)
{
	t_u16				op_arg_offset;

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
		op_dump(&proc->op, true, true);
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
