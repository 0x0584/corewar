/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/02/09 17:15:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

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

void print_arena(void)
{
	int i = 0;
	int fd;

	fd = open("arena.log", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (i < MEM_SIZE)
	{
		ft_dprintf(fd, "%02x ", g_vm.arena[i++]);
		if (i % 32 == 0)
			ft_dprintf(fd, "\n");
	}
	ft_dprintf(fd, "\n");
	close(fd);
}

t_st			vm_loop(void)
{
    t_st			st;

    while (!lst_empty(g_pool))
    {
    	lst_iter_arg(g_pool, true, &st, vm_read);
    	lst_iter_arg(g_pool, true, &st, vm_exec);
    	/* process_cleanup(); */
    	/* getchar(); */
    	/* draw_memory(); */
    }
    return (st_succ);
}

t_vm			g_vm = {.delta = CYCLE_TO_DIE};
int				g_fd;
