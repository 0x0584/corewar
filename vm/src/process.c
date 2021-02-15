/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 11:58:20 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

pid_t		g_pid = 1;
t_lst		g_pool = NULL;

t_proc		new_process(t_u8 player_num, t_pc at)
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

void		reset_alive(void *proc)
{
	(void)proc;
}

static void dump_reg(t_proc p)
{
	t_reg r;

	r = 1;
	ft_dprintf(g_fd, "   registers: [\n");
	while (r <= REG_NUMBER)
	{
		if (p->reg[r] != 0){
			ft_dprintf(g_fd, "     r%{yellow_fg}%-02d%{reset} ="
					   " 0x%08x { %{cyan_fg}short%{reset}: %10hd,"
					   " %{cyan_fg}int%{reset}: %10d }\n",
					   r, p->reg[r], p->reg[r], p->reg[r]);
		}
		r++;
	}
	ft_dprintf(g_fd, "  ]\n");
}

static void proc_dump(void *blob, size_t i)
{
	t_proc p;

	p = blob;
	(void)i;
	ft_dprintf(g_fd, " --- Process (%{green_fg}%{bold}%d%{reset}) of player %{green_fg}%hhu%{reset}"
			   " (at %{magenta_fg}0x%04x%{reset})",
			   p->pid,
			   p->num,
			   p->pc);
	ft_dprintf(g_fd, " holding: %{bold}%s%{reset} %{italic}with%{reset}",
			   p->op.name ? p->op.name : "fresh");
	ft_dprintf(g_fd, " carry: %{cyan_fg}%s%{reset}"
			   " lives: %{cyan_fg}%hu%{reset}\n",
			   p->carry ? "true" : "false", p->lives);
	dump_reg(p);
	ft_dprintf(g_fd, " ---\n");
}

void		process_dump(void)
{
	ft_dprintf(g_fd, "\n %{bold}####### %{green_fg}It's cycle"
			   " %{cyan_fg}%zu%{reset}%{bold}%{green_fg}"
			   " having %{cyan_fg}%zu%{reset}%{bold}%{green_fg} processe(s):%{reset}\n\n",
			   g_vm.cycles, lst_size(g_pool));
	lst_iteri(g_pool, true, proc_dump);
	ft_dprintf(g_fd, "\n %{bold}#########################################%{reset}\n\n");

}

static void kill_process(void)
{
	t_lstnode	walk;
	t_proc		p;

	walk = lst_front(g_pool);
	while (walk)
	{
		p = walk->blob;
		lst_node_forward(&walk);
		if (g_vm.delta < 0 || (!p->lives && p->op.callback))
			lst_remove_previous(g_pool, walk);
		else
			p->lives = 0;
	}
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
	check_vm();
	kill_process();
}
