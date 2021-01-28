/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:18:08 by archid-           #+#    #+#             */
/*   Updated: 2021/01/28 10:18:54 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
** \file process.h
*/

#ifndef PROCESS_H
# define PROCESS_H

# include "vmtypes.h"

typedef struct s_process	*t_proc;

/**
** \brief operations have at most three args, of size at most a 32-bit
**
** \param proc the calling process
** \param a first argument
** \param b second argument (if applicable)
** \param c third argument (if applicable)
*/
typedef void				(*t_op_callback)(t_proc proc);

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
	** \brief player number defined either by availability or
	** supplied as argument
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
** \brief union to retrieve the argument encoding from the encoding byte
*/
typedef union				u_args_encoding
{
	/**
	** \brief the encoding byte is big endian
	*/
	t_u8			encoding;

	/**
	** \brief arguments encoding is reverse because the encoding byte
	** is big endian
	*/
	struct					s_args
	{
		t_u8	padding:2;
		t_u8	arg_3:2;
		t_u8	arg_2:2;
		t_u8	arg_1:2;
	}				args;
}							t_args_encoding;

typedef union				u_args_value
{
	t_u32			value;
	struct					s_args_value
	{
		t_u8	byte_4;
		t_u8	byte_3;
		t_u8	byte_2;
		t_u8	byte_1;
	}				val;
}							t_args_value;

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
	** \brief diffrent operation have different label sizes, which affects
	** how much we're reading from memory.
	**
	** either we read 2 or 4 Bytes
	*/
	t_u8			label_size;

	/**
	** \brief some operations do not have an encoding Byte
	*/
	bool			encoded;

	/**
	** \brief the callback function which does the job
	*/
	t_op_callback	callback;

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
**	 in any case, we indicate the status of the call within the arg
**
** \param proc a process from `g_pool`
*/
void						op_callback(void *proc);

void						op_nop(t_proc proc);
void						op_live(t_proc proc);
void						op_ld(t_proc proc);
void						op_st(t_proc proc);
void						op_add(t_proc proc);
void						op_sub(t_proc proc);
void						op_and(t_proc proc);
void						op_or(t_proc proc);
void						op_xor(t_proc proc);
void						op_zjmp(t_proc proc);
void						op_ldi(t_proc proc);
void						op_sti(t_proc proc);
void						op_fork(t_proc proc);
void						op_lld(t_proc proc);
void						op_lldi(t_proc proc);
void						op_lfork(t_proc proc);
void						op_aff(t_proc proc);

/**
** \brief the global process id counter
**
**	 incremented with each new process
*/
extern pid_t				g_pid;

/**
** \brief the list of all alive processes
**
**	 each time we create a process, it is inserted into the pool, and removed
** when it is dead
*/
extern t_lst				g_pool;

/**
** \brief global arguments for operations
**
**   the size of 32-bit is at most the size required by all opearations
**
** \see op.h
*/
extern t_u32				g_args[];

#endif
