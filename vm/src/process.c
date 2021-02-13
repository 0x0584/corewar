/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/12 17:27:24 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

pid_t	g_pid = 1;
t_lst	g_pool = NULL;

t_proc	new_process(t_u8 player_num, t_pc at)
{
	t_proc	foo;

	foo = ft_calloc(1, sizeof(struct s_process));
	foo->pid = g_pid++;
	foo->num = player_num;
	foo->pc = at;
	g_pool = lst_push_front_blob(g_pool ? g_pool : lst_alloc(blob_free),
								 foo, sizeof foo, false);
	return (foo);
}

void	reset_alive(void *proc)
{
	(void)proc;
}

static void dump_reg(t_proc p)
{
	t_reg r;

	r = 1;
	ft_dprintf(g_fd, "Registers: [");
	while (r <= REG_NUMBER)
	{		
		ft_dprintf(g_fd, "   r%d = %08x short(%hd) int(%d)\n", r, p->reg[r], p->reg[r], p->reg[r]);
		r++;
	}
	ft_dprintf(g_fd, "]\n");
}

static void proc_dump(void *blob)
{
	t_proc p;

	p = blob;
	ft_dprintf(g_fd, "Player %hhu (%d at %hd): ", p->num, p->pid, p->pc, p->lives);
	dump_reg(p);
	ft_dprintf(g_fd, "carry: %s with lives: %hu", p->carry ? "true" : "false", p->lives);
	ft_dprintf(g_fd, " holding %s\n",  p->op.name);	
}

void	process_cleanup(void)
{
	g_vm.cycles++;
	ft_dprintf(g_fd, "It's cycle %u\n\n -------Processes:\n\n", g_vm.cycles);
	lst_iter(g_pool, true, proc_dump);
	ft_dprintf(g_fd, "\n -------\n\n");
	
	// lst_iter(g_pool, true, reset_alive);

	// check cycle to die
}
