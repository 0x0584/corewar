/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:27:15 by archid-           #+#    #+#             */
/*   Updated: 2021/02/16 19:19:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"


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
			  p->op.info.name ? p->op.info.name : "fresh");
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
