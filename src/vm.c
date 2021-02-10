/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/02/09 18:36:04 by archid-          ###   ########.fr       */
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

t_st			vm_loop(void)
{
    t_st			st;

	if (g_visu)
		draw_setup(true);
    while (!lst_empty(g_pool))
    {
    	lst_iter_arg(g_pool, true, &st, vm_read);
    	lst_iter_arg(g_pool, true, &st, vm_exec);
    	/* process_cleanup(); */
    	/* getchar(); */
    }
	if (g_visu)
    	draw_setup(false);
    return (st_succ);
}

int				g_fd;
t_vm			g_vm = {.delta = CYCLE_TO_DIE};

bool			g_visu = false;
