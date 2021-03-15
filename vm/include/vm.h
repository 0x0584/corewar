/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:32:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op_impl.h"
# include "champ_impl.h"

typedef t_champ		t_gladiators[MAX_PLAYERS];
typedef t_u8		t_memory[MEM_SIZE];

typedef struct		s_vm
{
	t_memory		arena;
	t_u8			nplayers;
	t_gladiators	champs;
	t_s32			cycles;
	t_s32			current_cycles;
	t_u8			n_checks;
	t_s16			delta;
	t_u16			lives;
	t_s16			or_delta;
	t_u8			winner;
}					t_vm;

t_st				parse_arguments(int ac, char *av[]);
t_st				vm_loop(void);
t_st				vm_decode(t_proc p, t_pc *offset);
void				vm_read(void *proc, void *arg);
void				vm_exec(void *proc, void *arg);
void				print_arena(void);
void				op_dump(const t_op *op, bool dump_args, bool dump_verbose);

extern t_vm			g_vm;
extern int			g_fd;

extern bool			g_show_logs;
extern bool			g_jumped;
#endif
