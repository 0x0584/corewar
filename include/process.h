/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:18:08 by archid-           #+#    #+#             */
/*   Updated: 2021/02/05 18:29:35 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
** \file process.h
*/

#ifndef PROCESS_H
# define PROCESS_H

# include "op_impl.h"

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
	**
	** `g_vm.arena` counter
	*/
	t_u16			pc;

	/**
	** \brief each process has it's own register
	*/
	t_u32			reg[REG_NUMBER];

	/**
	** \brief carry sis et by operations in case of either yielding zero,
	** overflow/underflow or error
	*/
	bool			carry;

	/**
	** \brief when called `op_live`
    */
	bool			alive;

	/**
	** \brief operation of the current process
	*/
	t_op			op;
};

/**
** \brief each number of `CYCLES_TO_DIE` we remove all process from `g_pool`
** forwhich they have not execuetd a `op_live` operation
**
** \see vm.h
** \see vm.c
*/
void						process_cleanup();

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
t_proc						new_process(t_u8 num, t_u16 at);

/**
** \brief shift the program counter of the process by an offset
**
**   - does *not* affect the process
**   - if the
**
** \param pc program counter of a process
** \param offset shifting
**
** \return shifted program counter
*/
t_u16						shift_pc(t_proc p, t_u16 offset);

t_u16						pc_shift(t_u16 pc, t_u16 offset, bool long_op);

/**
** \brief move the process program counter by an offset
** \param pc program counter of a process
** \param offset shifting
**
** \return new value of the program counter
*/
t_u16						move_pc(t_proc p, t_u16 offset);

t_u16						pc_move(t_u16 *pc, t_u16 offset, bool long_op);

/**
** \brief the global process id counter
**
**	 incremented with each new created process, call to new_process()
*/
extern pid_t				g_pid;

/**
** \brief the list of all alive processes
**
**	 each time we create a process, it is inserted into the pool, and removed
** when it is dead
*/
extern t_lst				g_pool;

#endif
