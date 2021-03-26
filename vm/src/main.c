/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:05 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 22:27:21 by mac              ###   ########.fr       */
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
	if (g_vm.winner == 0)
		st_log(st_fail, 2, "No winner");
	else
		ft_dprintf(g_fd, "Contestant %hhu, \"%s\", has won after %d cycles !\n",
					g_vm.winner, g_vm.champs[g_vm.winner - 1].prog_name, g_vm.cycles);
}

int				main(int argc, const char *argv[])
{
	int				ret;

	g_fd = 1;
	g_vm.winner = 0;
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
