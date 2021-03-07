/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:52 by archid-           #+#    #+#             */
/*   Updated: 2021/02/25 14:54:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"
#include "op_callback.h"

void				vm_read(void *proc, void *arg)
{
	t_proc	p;
	t_pc	old;

	p = proc;
	if (mem_at(p) >= op_count)
	{
		set_nop(p);
		old = p->pc;
		move_pc(p, 1);
		*(t_st *)arg = st_fail;
		ft_dprintf(g_fd ,"P %-4d | %02x is not a valid operation!\n", p->num, g_vm.arena[p->pc]);
		ft_dprintf(g_fd ,"ADV %hd (0x%04x -> 0x%04x)\n", p->pc - old, old, p->pc);
	}
	else if (!mem_at(p))
	{
		set_nop(p);
		old = p->pc;
		move_pc(p, 1);
		*(t_st *)arg = st_fail;
		ft_dprintf(g_fd ,"P %-4d | nop\n", p->num);

		ft_dprintf(g_fd ,"ADV %hd (0x%04x -> 0x%04x)\n", p->pc - old, old, p->pc);
	}
	else if (!p->op.callback || p->op.callback == nop || p->op.cycles > 0)
	{
		ft_memcpy(&p->op, &g_op[mem_at(p)], sizeof(t_op));
		p->op.cycles *= -1;
		*(t_st *)arg = st_succ;
		if (g_show_logs)
			ft_dprintf(g_fd, " >>> player %d: `%s` operation, scheduled after %d cycles\n", p->num, p->op.info.name, -p->op.cycles);
	}
}

/**
 ** \brief a register which has an argument of 1 Byte.
 **
 **	  - registers are defined inside a process with `REG_NUMBER` available
 **	  - call mem_chunk() reading REG_SIZE from which the *PC* is pointing
 **
 ** \param p process holding an operation on which we would like to match `arg`
 ** \param arg index of arg to of ht operation
 **
 ** \see op.h
 ** \see op_impl.h
 ** \see process.h
 **
 ** \return
 **
 **	  - `st_succ` if the arg referes to a register
 **	  - `st_fail` if the argument is not a register
 **	  - `st_error` if the argument is indeed a register, but not a *valid* one
 */
static inline t_st		handle_reg(t_proc p, t_arg arg, t_pc *offset)
{
	if (encoded(op_encoding(&p->op.info, arg)) == T_REG)
		if (1 <= mem_deref(p, *offset) && mem_deref(p, *offset) <= REG_NUMBER)
		{
			mem_chunk(p, arg, offset);
			return (st_succ);
		}
		else
		{
			if (g_show_logs)
				ft_dprintf(g_fd ," >>> %{red_fg}invalid register (%08b) access%{reset}\n", mem_deref(p, *offset));
			return (st_error);
		}
	else
		return (st_fail);
}

/**
** \brief indepandant from the type `T_IND` or `T_DIR`. mem_chunk() reads either a chunk
** or a short_chunk depending on the opeartion. also, mem_chunk() shall either
** read a chunk directly, or via a reference to the arena (memory)
**
** \see handle_reg()
** \see vm.h
** \see op.h
** \see op_impl.h
*/
t_st					handle_chunk(t_proc p, t_arg arg, t_pc *offset)
{
	if (encoded(op_encoding(&p->op.info, arg)) == T_DIR
			|| encoded(op_encoding(&p->op.info, arg)) == T_IND)
	{
		mem_chunk(p, arg, offset);
		return (st_succ);
	}
	else
	{
		if (g_show_logs)
			ft_dprintf(g_fd ," >>> %{red_fg}unknown encoding of arg %d%{reset}", arg);
		return (st_fail);
	}
}

static t_st				handle_arg(t_proc p, t_arg arg, t_pc *offset)
{
	t_st					st;

	if (arg < p->op.info.nargs)
	{
		if (g_show_logs)
			ft_dprintf(g_fd ," >>> encoding of %d (%02b)\n", arg, op_encoding(&p->op.info, arg));
	}
	else
	{
		if (g_show_logs)
			ft_dprintf(g_fd ," >>> %{red_fg}encoding is not padded (%02b)%{reset}\n", op_encoding(&p->op.info, arg));
		return st_fail;
	}
	if (op_meta_encoding(&p->op.info, arg) & encoded(op_encoding(&p->op.info, arg)))
	{
		if ((st = handle_reg(p, arg, offset)))
			if ((st = handle_chunk(p, arg, offset)))
				return (st);
	}
	else
	{
		if (g_show_logs)
			ft_dprintf(g_fd ," >>> %{red_fg}unexpected argument encoding %2b vs %8b%{reset}\n", op_encoding(&p->op.info, arg), op_meta_encoding(&p->op.info, arg));
		return st_fail;
	}
	return (st);
}

t_st					read_arg_chunk(t_proc p, t_pc *offset)
{
	t_arg					arg;
	t_st					st;

	arg = 0;
	while (encoded(op_encoding(&p->op.info, arg)) != T_PAD)
	{
		if ((st = handle_arg(p, arg, offset)))
			return (st);
		arg++;
	}
	if (arg == p->op.info.nargs)
		return (st_succ);
	else
	{
		if (g_show_logs)
			ft_dprintf(g_fd ," >>> %{red_fg}arguments are not padded (%08b)%{reset}\n", op_encoding(&p->op.info, arg));
		return (st_fail);
	}
}
