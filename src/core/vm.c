/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:58 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 16:36:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "player.h"

int		vm_loop(void)
{
	/*
	t_vm vm;

	if(!vm_init(&vm))
		return 1;
	while (true) {
		// fetcher
		vm_fetch(&vm);
        // vm_decode();
        // vm_execute();
	}
	*/
	return 0;
}

// flags: [-dump nbr_cycles] [[-n number] champion1.cor]
bool	parse_arguments(int ac, char *av[])
{
	int i;

	if (ac == 1)

		// sti r1, %:live, %10
		// 01 10 10 00

		// op: 0x0b
		// encoding byte: 0x68
		//
		// reg: 01
		// 00 0f 00
		// 01 06  64 01 00 00 00 00 01 01

		return (false);
    i = 1;
    while (i < ac)
	{
		if (ft_strsuffix(av[i], ".cor"))
			if (player_read(av[i], &g_gladiators[g_nplayers++]))
				return false;
        i++;
    }
	return (g_nplayers < 5 && g_nplayers);
}

/*
** Global Variables Defined in vm.h
*/
t_u8			g_nplayers = 0;
