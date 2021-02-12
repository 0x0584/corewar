/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/02/12 12:30:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"
#include "draw.h"

static char		*files[MAX_PLAYERS];

// flags: [-dump nbr_cycles] [[-n number] champion1.cor]
t_st			parse_arguments(int ac, char *av[])
{
	int				i;
	int				j;

	if (ac == 1)
		return (false);
	i = 1;
	j = 0;
	while (i < ac)
	{
		if (ft_strsuffix(av[i], ".cor"))
		{
			assert(j < MAX_PLAYERS);
			files[j++] = av[i];
		}
		i++;
	}
	assert(j <= MAX_PLAYERS);
	g_vm.nplayers = j;
	while (j--)
		if (player_read(files[j], j, g_vm.gladiators + j))
			return (false);
	return (true);
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

t_st			vm_loop(void)
{
    t_st			st;

	print_arena();

	if (g_visu)
		draw_setup(true);
    while (!lst_empty(g_pool))
    {
    	process_cleanup();
    	lst_iter_arg(g_pool, true, &st, vm_read);
    	lst_iter_arg(g_pool, true, &st, vm_exec);

		/* print_arena(); */
    }
	if (g_visu)
    	draw_setup(false);
    return (st_succ);
}

int				g_fd;
t_vm			g_vm = {.delta = CYCLE_TO_DIE};

bool			g_visu = false;
