/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:25:17 by archid-           #+#    #+#             */
/*   Updated: 2021/02/16 18:27:35 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

static void kill_process(void)
{
	t_lstnode	walk;
	t_proc		p;

	ft_dprintf(g_fd, " >>>>>>>>>>>>\n");
	walk = g_pool->head;
	while (walk->next != g_pool->tail)
	{
		p = walk->next->blob;
		if (g_vm.delta < 0 || (!p->lives && p->op.callback))
		{
			ft_dprintf(g_fd, " >>>>>>>>>>>> killed %d %s\n", p->pid, p->op.info.name);
			lst_remove_next(g_pool, walk);
		}
		else
		{
			p->lives = 0;
			lst_node_forward(&walk);
		}
	}
	ft_dprintf(g_fd, " >>>>>>>>>>>>\n");
}

static void check_vm(void)
{
	if (g_vm.lives >= NBR_LIVE || g_vm.n_checks + 1 == MAX_CHECKS)
	{
		g_vm.n_checks = 0;
		g_vm.delta -= CYCLE_DELTA;
	}
	else
		g_vm.n_checks++;
	g_vm.current_cycles = 0;
	g_vm.lives = 0;
}

void		process_cleanup(void)
{
	kill_process();
	check_vm();
}
