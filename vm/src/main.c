/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:05 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 18:51:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		print_usage(void)
{
	ft_putendl_fd("Usage: ./corewar [-dump N] [[-n N] *.cor]", 2);
	return (EXIT_FAILURE);
}

static void		declare_winner(void)
{
	if (g_vm.winner)
	{
		ft_dprintf(g_fd, "Contestant %hhu, \"%s\", has won !\n",
					g_vm.winner, g_vm.champs[g_vm.winner - 1].prog_name);
	}
	else
		ft_putendl("No Winner!!");
}

int				main(int argc, char *argv[])
{
	int				ret;

	g_fd = 1;
	if (parse_arguments(argc, argv))
	{
		vm_loop();
		declare_winner();
		ret = EXIT_SUCCESS;
	}
	else
	{
		print_usage();
		ret = EXIT_FAILURE;
	}
	return (ret);
}
