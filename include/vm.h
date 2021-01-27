/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/01/26 10:10:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <assert.h>
# include "player.h"

/**
** \brief at most we have `MAX_PLAYERS`
** \see op.h
*/
typedef t_player	t_players[MAX_PLAYERS];

typedef struct		s_vm
{
    /**
    ** \brief the VM's random access memory space
    */
    t_memory	arena;

    /**
    ** \brief Arena Memory colors
    ** \see draw.h
    */
    t_memory	colors;

    /**
    ** \brief number of player read via command line args
    */
    t_u8		nplayers;

    /**
    ** \brief players read via command line arguments
    */
    t_players	gladiators;

	/**
	** \brief how many cycles has the game been running
	*/
	t_u32		cycles;

	/**
	** \brief cycles to die keeps on diminishing. initialized with `CYCLE_TO_DIE`
	*/
	t_u16		delta;

	/**
	** \brief how many lives have been executed since last delta
	*/
	t_u16		lives;

    /**
    ** \brief id of last player that reported alive
    */
    t_s8		winner;
}					t_vm;

/**
** \brief output the usage of the program to stdout
**
** \return -1 always
*/
int		        	print_usage(void);

/**
** \brief  parse command-line arguments and initialize VM's global variables
**
** \param ac argument counter
** \param av arguments vector
**
** \return `true` if the arguments are correct, `false` otherwise.
*/
bool	        	parse_arguments(int ac, char *av[]);

/**
** \brief this is the instruction cycle for all running processes. it fetches,
** decodes and execute instructions of each process sequentially in
** reverse `t_proc::num` order.
**
** \return `st_succ` in case the game is terminated, `st_error` otherwise.
*/
t_st				vm_loop(void);

/*
** Memory
*/

/**
** \brief load the players into memory from `t_vm::gladiators` and set
** them evenly spaced
**
** \return if succeeded, `st_succ` is return, otherwise `st_error`
**
** \see memory.c
*/
t_st				mem_load(void);

/*
** Clock
*/

/**
** \brief the clock synchronise the running processes based on
** their `t_proc::num`
**
** \return `st_error` in case fetch is not successful. Otherwise`st_succ`
** in case all process have fetched or `st_fail` if they haven't
**
** \see clock.c
*/
t_st				clock_tick(void);

/**
** \brief reverse a word (32-bit) from little endian to big endian
**
** \param word little endian word
**
** \return big endian word
*/
t_u32				beword(t_u32 word);

/**
** \brief reverse a byte (8-bits) from little endian to big endian
**
** \param word little endian byte
**
** \return big endian byte
*/
t_u8				bebyte(t_u8 byte);

/**
** \brief Virtual Machine
*/
extern t_vm			g_vm;

#endif
