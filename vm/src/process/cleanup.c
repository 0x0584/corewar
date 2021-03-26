/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:25:17 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 18:50:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

int			g_fd_check;

static void		kill_processes(void)
{
	t_lstnode	walk;
	t_proc		p;

	walk = g_pool->head;
	while (walk->next != g_pool->tail)
	{
		p = walk->next->blob;
		if (g_vm.cycles - p->last_live >= g_vm.delta)
		{
			if (g_verbose & show_deaths)
				ft_dprintf(g_fd,
							"Process %d hasn't lived for %d cycles (CTD %hd)\n",
							p->pid, g_vm.cycles - p->last_live, g_vm.or_delta);
			lst_remove_next(g_pool, walk);
		}
		else
		{
			p->lives = 0;
			lst_node_forward(&walk);
		}
	}
}

void			process_cleanup(void)
{
	g_vm.n_checks++;
	kill_processes();
	if (g_vm.lives >= NBR_LIVE || g_vm.n_checks == MAX_CHECKS)
	{
		g_vm.n_checks = 0;
		g_vm.delta -= CYCLE_DELTA;
		g_vm.or_delta = g_vm.delta;
		if (g_vm.delta <= 0)
			g_vm.delta = 1;
		if (g_verbose & show_deaths)
			ft_dprintf(g_fd, "Cycle to die is now %d with (%zu Processe(s))\n",
					   g_vm.or_delta, lst_size(g_pool));
	}
	g_vm.current_cycles = 0;
	g_vm.lives = 0;
}
