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

static bool		g_dump_arena = true;

static void		set_vm(void)
{
	g_fd_check = open("cycles.log", O_RDWR | O_CREAT | O_TRUNC, 0777);
	set_ops();
	if (g_dump_arena)
		print_arena();
}

static void		unset_vm(void)
{
	close(g_fd_check);
}

t_st			vm_loop(void)
{
	t_st			st;

	set_vm();
	print_arena();
	while (!lst_empty(g_pool))
	{
		g_vm.cycles++;
		g_vm.current_cycles++;
		if (g_verbose & show_cycles)
			ft_dprintf(g_fd, "It is now cycle %d\n", g_vm.cycles);
		lst_iter_arg(g_pool, true, &st, vm_read);
		lst_iter_arg(g_pool, true, &st, vm_exec);
		if (g_vm.current_cycles == g_vm.delta)
			process_cleanup();
	}
	unset_vm();
	return (st_succ);
}

void			print_arena(void)
{
	int fd;
	int i;

	i = 0;
	fd = open("arena.log", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_dprintf(fd, "Cycle: %u\nNumber of Process: %zu\n",
	g_vm.cycles, lst_size(g_pool));
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_dprintf(fd, "0x%04x : ", i);
		ft_dprintf(fd, "%02x ", g_vm.arena[i++]);
		if (i % 64 == 0)
			ft_dprintf(fd, "\n");
	}
	ft_putendl_fd("", fd);
	close(fd);
}

int				g_fd;
t_vm			g_vm = {.delta = CYCLE_TO_DIE, .or_delta = CYCLE_TO_DIE};

bool			g_visu = false;
bool			g_show_logs = false;
