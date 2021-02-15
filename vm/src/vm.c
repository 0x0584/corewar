/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 12:03:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"
#include "draw.h"

static bool		g_dump_arena = true;

static void		set_vm(void)
{
	if (g_visu)
		draw_setup(true);
	if (g_dump_arena)
		print_arena();
}

static void		unset_vm()
{
	if (g_visu)
    	draw_setup(false);
}

 void dummy(void) {
	process_dump();
 }

t_st			vm_loop(void)
{
    t_st			st;

	set_vm();
	process_dump();
    while (!lst_empty(g_pool))
    {
		g_vm.cycles++;
		g_vm.current_cycles++;
    	lst_iter_arg(g_pool, true, &st, vm_read);
    	lst_iter_arg(g_pool, true, &st, vm_exec);
		if (g_vm.cycles == 94 || g_vm.cycles == 155)
			dummy();
		if (g_vm.current_cycles == g_vm.delta || g_vm.delta < 0)
		{
			process_dump();
			process_cleanup();
			usleep(5000);
		}
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
	/* ft_dprintf(fd, "0x%04x : ", 0); */
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
t_vm			g_vm = {.delta = CYCLE_TO_DIE, .lives = 0};

bool			g_visu = false;
