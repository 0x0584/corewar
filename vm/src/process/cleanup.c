/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:25:17 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 08:44:36 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

int			g_fd_check;

static void		kill_process(void)
{
	t_lstnode	walk;
	t_proc		p;

	walk = g_pool->head;
	while (walk->next != g_pool->tail)
	{
		p = walk->next->blob;
		if (g_vm.cycles - p->last_live >= g_vm.delta)
		{
			ft_dprintf(g_fd_check, "killed %d %s\n", p->pid, p->op.info.name);
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

static void		check_vm(void)
{
	ft_dprintf(g_fd_check, "Cycle %d: ", g_vm.cycles);
	g_vm.n_checks++;
	if (g_vm.lives >= NBR_LIVE || g_vm.n_checks == MAX_CHECKS)
	{
		g_vm.n_checks = 0;
		g_vm.delta -= CYCLE_DELTA;
		g_vm.or_delta = g_vm.delta;
		if (g_vm.delta <= 0)
			g_vm.delta = 1;
		ft_dprintf(g_fd_check, " new delta %hd\n", g_vm.or_delta);
		ft_dprintf(g_fd, "Cycle to die is now %d\n", g_vm.or_delta);
	}
	else
	{
		ft_dprintf(g_fd_check, " check number: %hhu\n", g_vm.n_checks);
	}
	g_vm.current_cycles = 0;
	g_vm.lives = 0;
}

void			process_cleanup(void)
{
	kill_process();
	check_vm();
}
