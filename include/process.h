/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:18:08 by archid-           #+#    #+#             */
/*   Updated: 2021/01/27 12:18:17 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
** \file process.h
*/

#ifndef PROCESS_H
# define PROCESS_H

#include "vmtypes.h"

/**
** \brief size after which re-allocate the hashtable
*/
# define PROCESS_CLEANUP_AFTER								0x80

typedef struct s_process	*t_proc;

/**
** \brief a process (child) is create using fork() syscall, each process is
** associated with a player number (parent).
*/
struct						s_process
{

	/**
	** \brief process id is the next available `g_pid`
	*/
    pid_t			pid;

	/**
	** \brief player number defined either by availability or supplied as argument
	*/
    t_u8			num;

    /**
    ** \brief program counter keeps points to the next-to-be-executed for the
    ** corresponding player
    */
    t_addr			pc;

	/**
	** \brief each process has it's own register
	*/
	t_u32			reg[REG_NUMBER];

	/**
	** \brief carry sis et by operations in case of either yielding zero,
	** overflow/underflow or error
	*/
	bool			carry;
};

/**
** \brief creates a process for a player and place the PC at `at`
**
** if the child is `true` then we supply the player number to `t_proc::reg[0]`
**
** \param num player number
** \param at address at the player's core file
** \param child whether this is the main player process
**
** \return a new process with the next available pid
*/
t_proc						new_process(t_u8 num, t_addr at, bool child);

/**
** \brief the global process id counter
**
**   incremented with each new process
*/
extern pid_t				g_pid;

/**
** \brief the list of all alive processes
**
**   each time we create a process, it is inserted into the pool, and removed
** when it is dead
*/
extern t_lst				g_pool;


/**
** \brief operations have at most three args, of size at most a 32-bit
**
** \param proc the calling process
** \param a first argument
** \param b second argument (if applicable)
** \param c third argument (if applicable)
*/
typedef void				(*t_op_callback)(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);

/**
** \brief each opeartions has a callback function which takes some number of
** arguments of one or various types. In addition, it shall take a number of
** cycles before it got executed
*/
typedef struct				s_op
{
	/**
	** \brief operation name as a string used to log the current operation
	*/
	const char		*op_name;

	/**
	** \brief the callback function which does the job
	*/
	t_op_callback	op;

	/**
	** \brief the number of cycles for an instruction to be executed
	**
	** it is part of the simulation where instruction take different periods
	*/
	t_u16			cycles;

	/**
	** \brief number of arguments the operation takes
	*/
	t_u8			nargs;

	/**
	** \brief argument types
	**
	** \see op.h
	*/
	t_arg_type		args[MAX_ARGS_NUMBER];
}							t_op;

/**
** \brief this routine is call on all process in reverse creation order, it
** fetches the opcode from the PC of each process and executes it.
**
**   in any case, we indicate the status of the call within the arg
**
** \param proc a process from `g_pool`
*/
void						op_callback(void *proc);

void                    	op_nop(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_live(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_ld(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_st(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_add(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_sub(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_and(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_or(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_xor(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_zjmp(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_ldi(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_sti(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                    	op_fork(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_lld(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_lldi(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_lfork(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);
void                        op_aff(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c);

#endif
