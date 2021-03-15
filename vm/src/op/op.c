/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:37:36 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 08:38:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"
#include "memory.h"

void		set_nop(t_proc p)
{
	ft_memcpy(&p->op, &g_op[op_nop], sizeof(t_op));
}

void		nop(t_proc proc)
{
	(void)proc;
}

void		live(t_proc proc)
{
	t_dir id;

	g_vm.lives++;
	proc->lives++;
	if ((id = -arg_value(proc, 0, false)) > 0 && id <= g_vm.nplayers)
	{
		g_vm.winner = id;
		ft_dprintf(g_fd, "Player %d (%s) is said to be alive\n",
					id, g_vm.champs[id - 1].prog_name);
		proc->last_live = g_vm.cycles;
	}
}

void		zjmp(t_proc proc)
{
	t_ind addr;

	addr = arg_value(proc, 0, false);
	ft_dprintf(g_fd, "zjmp %hd ", addr);
	if ((g_jumped = proc->carry))
		proc->pc = shift_pc(proc, addr);
	ft_putendl_fd(proc->carry ? "OK" : "FAILED", g_fd);
}

void		aff(t_proc proc)
{
	t_dir		c;

	if (ft_isprint(c = arg_value(proc, 0, false)))
		ft_printf("AFF: %c\n", c);
	else
		ft_printf("AFF: %x\n", c);
}
