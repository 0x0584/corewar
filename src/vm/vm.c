/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 17:30:45 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

static t_u8 lookup[] = {
	0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
	0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf,
};

t_u8	bebyte(t_u8 byte)
{
	return ((lookup[byte & 0x0f] << 4) | lookup[byte >> 4]);
}

/* Big Endian Word -- 32-bit */
t_u32 beword(t_u32 word)
{
    return (((word >> 24) & 0xff) | ((word << 8) & 0xff0000) |
			((word >> 8) & 0xff00) | ((word << 24) & 0xff000000));
}

static void process_cleanup()
{
	// if cycles to die remove process whom does not
}

t_st	vm_loop(void)
{
    t_st st;

    if ((st = mem_load()))
        return (st);
    while (!lst_empty(g_pool))
	{
		g_vm.cycles++;
        lst_iter(g_pool, true, vm_read);
		getchar();
		lst_iter(g_pool, true, vm_exec);
		/* process_cleanup(); */
		/* getchar(); */
        /* draw_memory(); */
    }
    return (st_succ);
}

// flags: [-dump nbr_cycles] [[-n number] champion1.cor]
bool		parse_arguments(int ac, char *av[])
{
	int			i;

	if (ac == 1)
		return (false);
	i = 1;
	while (i < ac)
	{
		if (ft_strsuffix(av[i], ".cor"))
			if (player_read(av[i], &g_vm.gladiators[g_vm.nplayers++]))
				return false;
		i++;
	}
	return (g_vm.nplayers < 5 && g_vm.nplayers);
}

int			print_usage(void)
{
	ft_putendl_fd("Usage: ./corewar [-dump N] [[-n N] *.cor]", 2);
	return -1;
}

t_vm		g_vm = {.delta = CYCLE_TO_DIE};
