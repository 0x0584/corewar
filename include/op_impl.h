/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2021/02/01 19:38:12 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
#ifndef OP_IMPL_H
#define OP_IMPL_H

# include "op.h"

/**
** \brief all operations have a `callback` function
**
** \see op.h
*/
enum						e_operations
{
	op_nop,			op_live,       op_ld,
	op_st,      	op_add,        op_sub,
	op_and,     	op_or,         op_xor,
	op_zjmp,    	op_ldi,        op_sti,
	op_fork,    	op_lld,        op_lldi,
	op_lfork,   	op_aff,

	op_count
};

/**
** \brief operations have at most three args, of size at most a 32-bit
**
** \param proc the calling process
** \param a first argument
** \param b second argument (if applicable)
** \param c third argument (if applicable)
**
** \see op_impl.h
*/
typedef void				(*t_op_callback)(t_proc proc);

/**
** \brief each opeartions has a callback function which takes some number of
** arguments of one or various types. In addition, it shall take a number of
** cycles before it got executed
**
** \see op.h
*/
typedef struct				s_op
{
	/**
	** \brief operation name as a string used to log the current operation
	*/
	const char			*name;

	/**
	** \brief operation docs
	*/
	const char			*doc;

	/**
	** \brief the callback function which does the job
	*/
	const t_op_callback	callback;

	/**
	** \brief a singular argument type require at most 4-bits to be stored
	**
	**   hence 3-Bytes should handle `MAX_ARGS_NUMBER`. the remainning Bytez
	**   indicates the number an operation takes, the the chunk size.
	**
	**   Also, if the operation is encoded and if it is a long operation.
	**
	**    padding  chunk size  encoded  long           args
	**    [00000]  [0]         [0]      [0]    [0000 | 0000 | 0000]
	**
	**   meta has little endianess
	**
	** \see op.h
	*/
	const t_op_meta		meta;

	/**
	** \brief the number of cycles for an instruction to be executed
	**
	** it is part of the simulation where instruction take different periods
	*/
	t_s16				cycles;

	/**
	** \brief some operation does *not* have a parameter encoding byte
	*/
	t_op_encoding		encoding;

	/**
    ** \brief global arguments for operations
	**
	**   the size of 32-bit is at most the size required by all opearations
	**
	** \see op.h
	*/
	t_blob				args;
}							t_op;

/**
** \brief this routine is call on all process in reverse creation order,
** it fetches the opcode from the PC of each process and executes it.
**
**	 in any case, we indicate the status of the call within the arg
**
** \param proc a process from `g_pool`
*/
void						callback(void *proc);

/**
** \brief operation interact with the VM's memory address range `arena`
** by either reading or writing to it. they also interact with process
** and might read/alter program counter and carry
*/
extern t_op					g_ops[op_count];

#endif
