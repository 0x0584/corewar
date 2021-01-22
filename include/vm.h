/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 10:36:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "player.h"

typedef struct s_vm t_vm;
typedef t_player	t_players[MAX_PLAYERS];

int		        	vm_loop(void);
bool	        	vm_init(t_vm *vm);
void 	        	vm_fetch(t_vm *vm);
t_op	        	vm_decode(t_addr *op);

int		        	print_usage(void);
bool	        	parse_arguments(int ac, char *av[]);


/* memory */

void				mem_load(void);

extern t_u8			g_nplayers;	  /* based on command line args */
extern t_memory		g_arena;	  /* memory */
extern t_players	g_gladiators; /* players */


#endif
