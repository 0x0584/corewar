/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/02/04 18:03:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "player.h"
# include "op.h"

/**
** \brief at most we have `MAX_PLAYERS`
** \see op.h
*/
typedef t_player	t_players[MAX_PLAYERS];


/**
** \brief memory is circular
**
** long operations access memory via a `MEM_SIZE` mod
** while regular operations use `IDX_MODE` mod
*/
typedef t_u8		t_memory[MEM_SIZE];

/**
** \brief
*/
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


/**
 * \brief decode the arguments of operation who's held by the process
 *
 * \param p the holding process
 * \param offset out reference reflecting the size of the decoded chunk
 *
 * \return `
 */
t_st				vm_decode(t_proc p, t_u8 *offset);

/**
** \brief callback to list of processes `g_pool` to read operation and
** set the waiting cycle of the operation
**
**  if the operation is valid, we reverse it waiting cycles
**
** \param proc process to read from
*/
void				vm_read(void *proc, void *arg);

/**
** \brief callback to list of processes `g_pool` to execute operations are ready
** to be executed.
**
**	- the waiting cycle is defined inside the opeartion. as we make a copy of
**	the operation `g_ops` at process creation time.
**	- at read, the number of cycles is reversed to indicate change
**
** \param proc a process ready to be executed
**
** \see op_impl.h
** \see vm_read()
*/
void				vm_exec(void *proc, void *arg);

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

/**
** \brief read arguments of an operation held by process `p`
** sets tjhe offset of the chunk
**
** \param p process of operation
** \param offset out reference of the chunk offset
**
** \return
**
**   - `st_succ`
*/
t_st				read_arg_chunk(t_proc p, t_u8 *offset);

/**
** \brief reads a `chuck_size` relative to the process's program counter
**
**   except registers, which have a `chunk_size` of `REG_SIZE`.
**   It is deduced from the encoding and whether the operation
**   have an `IDX_MOD`
**
**  \param p a reading process holding the program counter
**  \param value a reference to where to write the content
**
**  \return
**     - `st_succ` in case the of a successful read
**     - `st_error` might arise in case of invalid register addressing
*/
t_st				mem_chunk(t_proc p, t_arg arg);

/**
** \brief get the value of the memory address on which the
** program counter is pointing
**
** \param p process holding the program counter
** \param offset from which we shall be reading
**
** \return a byte
*/
t_u8				mem_deref(t_proc p, t_u16 offset);

/**
** \brief get the value of the memory address on which the
** program counter is pointing
**
** \param p process holding the program counter
**
** \return a byte
*/
t_u8				mem_at(t_proc p);

t_u8				at_mem(t_u16 p);

/*
** Little to Big Endian
*/

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
