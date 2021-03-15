/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:52 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:47:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"
#include "op_callback.h"

void					vm_read(void *proc, void *arg)
{
	t_proc	p;

	p = proc;
	if (!p->op.callback || p->op.callback == nop || p->op.cycles > 0)
	{
		if (!g_vm.arena[p->pc] || g_vm.arena[p->pc] >= op_count)
		{
			set_nop(p);
			move_pc(p, 1);
			*(t_st *)arg = st_fail;
		}
		else
		{
			ft_memcpy(&p->op, &g_op[mem_at(p)], sizeof(t_op));
			p->op.cycles *= -1;
			*(t_st *)arg = st_succ;
		}
	}
}

static inline t_st		handle_reg(t_proc p, t_arg arg, t_pc *offset)
{
	if (decode(op_encoding(&p->op.info, arg)) != T_REG)
		return (st_fail);
	if (1 <= mem_deref(p, *offset) && mem_deref(p, *offset) <= REG_NUMBER)
	{
		mem_chunk(p, arg, offset);
		return (st_succ);
	}
	else
		return (st_error);
}

t_st					handle_chunk(t_proc p, t_arg arg, t_pc *offset)
{
	if (decode(op_encoding(&p->op.info, arg)) == T_DIR
			|| decode(op_encoding(&p->op.info, arg)) == T_IND)
	{
		mem_chunk(p, arg, offset);
		return (st_succ);
	}
	else
		return (st_fail);
}

static t_st				handle_arg(t_proc p, t_arg arg, t_pc *offset)
{
	t_st					st;

	if (arg >= p->op.info.nargs)
		return (st_fail);
	if (op_meta_encoding(&p->op.info, arg) & decode(op_encoding(&p->op.info,
																	arg)))
	{
		if ((st = handle_reg(p, arg, offset)))
			if ((st = handle_chunk(p, arg, offset)))
				return (st);
	}
	else
		return (st_fail);
	return (st);
}

t_st					read_arg_chunk(t_proc p, t_pc *offset)
{
	t_arg					arg;
	t_st					st;

	arg = 0;
	while (decode(op_encoding(&p->op.info, arg)) != T_PAD)
	{
		if ((st = handle_arg(p, arg, offset)))
			return (st);
		arg++;
	}
	if (arg == p->op.info.nargs)
		return (st_succ);
	else
		return (st_fail);
}
