/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:52 by archid-           #+#    #+#             */
/*   Updated: 2021/02/04 18:04:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

/**
** \brief a register which has an argument of 1 Byte.
**
**   - registers are defined inside a process with `REG_NUMBER` available
**   - call mem_chunk() reading REG_SIZE from which the *PC* is pointing
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
**   - `st_succ` if the arg referes to a register
**   - `st_fail` if the argument is not a register
**   - `st_error` if the argument is indeed a register, but not a *valid* one
*/
static inline t_st		handle_reg(t_proc p, t_arg arg, t_u8 *offset)
{
	if (encoded(arg) == T_REG)
		if (mem_deref(p, arg) >= REG_NUMBER)
			return (LOGGER(st_error, "invalid register (%d) access\n", mem_deref(p, 1)));
		else
		{
			*offset += mem_chunk(p, arg);
			return (st_succ);
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
static inline t_st		handle_chunk(t_proc p, t_arg arg, t_u8 *offset)
{
	if (encoded(arg) == T_DIR || encoded(arg) == T_IND)
	{
		*offset += mem_chunk(p, arg);
		return (st_succ);
	}
	else
		return LOGGER(st_fail, "unknown encoding",);
}

t_st					read_arg_chunk(t_proc p, t_u8 *offset)
{
	t_arg	arg;
	t_st	st;

	arg = 0;
	while (arg < p->op.nargs)
	{
	    if (op_encoding(p, arg << 2) | encoded(arg))
		{
			if ((st = handle_reg(p, arg, offset)))
				if ((st = handle_chunk(p, arg, offset)))
					return (st);
		}
		else
			return LOGGER(st_fail, "unexpected argument encoding %2b vs %8b",
						  op_encoding(p, arg << 2), op_meta_encoding(arg, which));
		arg++;
	}
	if (op_encoding(p, arg << p->op.nargs))
		return (LOGGER(st_fail, "arguments are not padded\n",));
	return (st_succ);
}

void	vm_read(void *proc, void *arg)
{
	t_proc	p;
	p = proc;
    if ((p->carry = mem_at(p) >= op_count))
	{
		*(t_st *)arg = LOGGER(st_fail, "player %d: %02x is not an operation\n",
							  p->num, g_vm.arena[p->pc]);
		p->op = g_ops[op_nop];
		move_pc(p, 1);
	}
	else if (p->op.cycles > 0)
	{
		p->op = g_ops[mem_at(p)];
		p->op.cycles *= -1;
		*(t_st *)arg = LOGGER(st_succ, "player %d: `%s` operation, scheduled after %d cycles\n",
							  p->num, p->op.name, p->op.cycles);
	}
}
