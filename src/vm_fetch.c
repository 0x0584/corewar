/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fetch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:24:15 by archid-           #+#    #+#             */
/*   Updated: 2021/01/19 15:25:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		vm_fetch_player(t_player *p)
{
	p->mar = p->pc++;				// save the address of PC
}

void			vm_fetch(t_vm *vm)
{
	short i;

	i = 0;
	while (i < MAX_PLAYERS && vm->players[i].file)
		vm_fetch_player(&vm->players[i++]);
}
