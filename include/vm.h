/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/01/12 17:40:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "player.h"

typedef struct s_vm t_vm;

struct				s_vm
{
	t_player players[MAX_PLAYERS];
};


int			vm_loop(void);
bool		vm_init(t_vm *vm);

void 		vm_fetch(t_vm *vm);

t_op		vm_decode(t_addr *op);

int			print_usage(void);
bool		parse_arguments(int ac, char *av[]);

#endif
