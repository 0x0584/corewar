/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:52 by archid-           #+#    #+#             */
/*   Updated: 2021/02/11 09:11:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"

void				vm_read(void *proc, void *arg)
{
	t_proc	p;

	p = proc;
	if (mem_at(p) >= op_count)
	{
		set_nop(p);
		move_pc(p, 1);
		*(t_st *)arg = st_fail;
		ft_dprintf(g_fd ,"player %d: %02x is not a valid operation!\n", p->num, g_vm.arena[p->pc]);
	}
	else if (p->op.cycles >= 0)
	{
		ft_memcpy(&p->op, &g_ops[mem_at(p)], sizeof(t_op));
		p->op.cycles *= -1;
		*(t_st *)arg = st_succ;
		ft_dprintf(g_fd, "player %d: `%s` operation, scheduled after %d cycles\n", p->num, p->op.name, -p->op.cycles);
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
static inline t_st		handle_reg(t_proc p, t_arg arg, t_u16 *offset)
{
	if (encoded(op_encoding(p, arg)) == T_REG)
		if (1 <= mem_deref(p, *offset) && mem_deref(p, *offset) <= REG_NUMBER)
		{
			mem_chunk(p, arg, offset);
			return (st_succ);
		}
		else
		{
			ft_dprintf(g_fd ,"invalid register (%08b) access\n", mem_deref(p, *offset));
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
t_st					handle_chunk(t_proc p, t_arg arg, t_u16 *offset)
{
	if (encoded(op_encoding(p, arg)) == T_DIR
			|| encoded(op_encoding(p, arg)) == T_IND)
	{
		mem_chunk(p, arg, offset);
		return (st_succ);
	}
	else
	{
		ft_dprintf(g_fd ,"unknown encoding of arg %d", arg);
		return (st_fail);
	}
}

static t_st				handle_arg(t_proc p, t_arg arg, t_u16 *offset)
{
	t_st					st;

	if (arg < p->op.nargs)
		ft_dprintf(g_fd ," encoding of %d (%02b)\n", arg, op_encoding(p, arg));
	else
	{
		ft_dprintf(g_fd ," encoding is not padded (%02b)\n", op_encoding(p, arg));
		return st_fail;
	}
	if (op_meta_encoding(p, arg) & encoded(op_encoding(p, arg)))
	{
		if ((st = handle_reg(p, arg, offset)))
			if ((st = handle_chunk(p, arg, offset)))
				return (st);
	}
	else
	{
		ft_dprintf(g_fd ," unexpected argument encoding %2b vs %8b\n", op_encoding(p, arg), op_meta_encoding(p, arg));
		return st_fail;
	}
	return (st);
}

t_st					read_arg_chunk(t_proc p, t_u16 *offset)
{
	t_arg					arg;
	t_st					st;

	arg = 0;
	while (encoded(op_encoding(p, arg)) != T_PAD)
	{
		if ((st = handle_arg(p, arg, offset)))
			return (st);
		arg++;
	}
	if (arg == p->op.nargs)
		return (st_succ);
	else
	{
		ft_dprintf(g_fd ," arguments are not padded (%08b)\n", op_encoding(p, arg));
		return (st_fail);
	}
}
