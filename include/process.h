/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:18:08 by archid-           #+#    #+#             */
/*   Updated: 2021/01/24 10:19:55 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	** \brief process id
	*/
    pid_t		pid;

	/**
	** \brief player number
	*/
    t_u8		num;

    /**
    ** \brief program counter keeps points to the next-to-be-executed for the
    ** corresponding player
    */
    t_addr		pc;

	/**
	** \brief each process has it's own register
	*/
	t_u32		reg[REG_NUMBER];

	/**
	** \brief carry sis et by operations in case of either yielding zero,
	** overflow/underflow or error
	*/
	bool		carry;
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

extern pid_t				g_pid;
extern t_lst				g_pool;

#endif
