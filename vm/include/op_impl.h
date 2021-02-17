/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2021/02/12 11:08:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
#ifndef OP_IMPL_H
#define OP_IMPL_H

# include "op.h"

typedef t_s32				t_reg;
typedef t_s16				t_pc;

/**
** \brief each created process is a node of `g_pool`.
**
**   it carries an opeartion a if executed by vm_loop() after
**   waiting for a number of cycles
**
** \see process.h
*/
typedef struct s_process	*t_proc;

/**
** \brief operations have at most three args, of size at most a 32-bit
**
** \param proc the calling process
** \param a first argument
** \param b second argument (if applicable)
** \param c third argument (if applicable)
**
** \return op status
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
typedef struct				s_operation
{
	t_op_info			info;
	
	/**
	** \brief the callback function which does the job
	*/
	const t_op_callback	callback;

	/**
	** \brief the number of cycles for an instruction to be executed
	**
	** it is part of the simulation where instruction take different periods
	*/
	t_s16				cycles;
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

void						set_nop(t_proc p);

#endif
