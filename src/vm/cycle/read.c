/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:52 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 17:29:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

void	vm_read(void *proc)
{
	t_proc	p;

	p = proc;
    if ((p->carry = mem_deref(p) >= op_count))
	{
		ft_dprintf(2, "player %d: %02x is not an operation\n", p->num, g_vm.arena[p->pc]);
		p->op = g_ops[op_nop];
		move_pc(p, 1);
	}
	else if (p->op.cycles > 0)
	{
		p->op = g_ops[g_vm.arena[p->pc]];
		p->op.cycles *= -1;
		ft_dprintf(2, "player %d: `%s` operation, scheduled after %d cycles\n",
				   p->num, p->op.name, p->op.cycles);
	}
}
