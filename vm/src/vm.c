/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 18:45:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

void			dump_arena(void)
{
	int i;

	i = 0;
	ft_dprintf(2, "Cycle: %u\nNumber of Process: %zu\n",
	g_vm.cycles, lst_size(g_pool));
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_dprintf(2, "0x%04x : ", i);
		ft_dprintf(2, "%02x ", g_vm.arena[i++]);
		if (i % 64 == 0)
			ft_dprintf(2, "\n");
	}
	ft_putendl_fd("", 2);
}

t_st			vm_loop(void)
{
	t_st			st;

	set_ops();
	while (!lst_empty(g_pool))
	{
		g_vm.cycles++;
		g_vm.current_cycles++;
		if (g_vm.cycles == g_dump)
		{
			dump_arena();
			break;
		}
		if (g_verbose & show_cycles)
			ft_dprintf(g_fd, "It is now cycle %d\n", g_vm.cycles);
		lst_iter_arg(g_pool, true, &st, vm_read);
		lst_iter_arg(g_pool, true, &st, vm_exec);
		if (g_vm.current_cycles == g_vm.delta)
			process_cleanup();
	}
	if (g_dump < 0)
		dump_arena();
	lst_del(&g_pool);
	return (st_succ);
}

int				g_fd;
t_vm			g_vm = {.delta = CYCLE_TO_DIE, .or_delta = CYCLE_TO_DIE};

bool			g_visu = false;
bool			g_show_logs = false;
