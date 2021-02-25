/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/02/25 10:23:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op_impl.h"
# include "player.h"

/**
** \brief at most we have `MAX_PLAYERS`
** \see op.h
*/
typedef t_champ		t_players[MAX_PLAYERS];

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
	t_s32		cycles;

	t_s32		current_cycles;

	t_u8		n_checks;

	/**
	** \brief cycles to die keeps on diminishing. initialized with `CYCLE_TO_DIE`
	*/
	t_s16		delta;


	/**
	** \brief how many lives have been executed since last delta
	*/
	t_u16		lives;

    /**
    ** \brief id of last player that reported alive
    */
    t_u8		winner;
}					t_vm;

/**
** \brief  parse command-line arguments and initialize VM's global variables
**
** \param ac argument counter
** \param av arguments vector
**
** \return `true` if the arguments are correct, `false` otherwise.
*/
t_st	        	parse_arguments(int ac, char *av[]);

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
t_st				vm_decode(t_proc p, t_pc *offset);

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

void				print_arena(void);

void				op_dump(const t_op *op, bool dump_args, bool dump_verbose);

/**
** \brief Virtual Machine
*/
extern t_vm			g_vm;
extern int			g_fd;

#endif
