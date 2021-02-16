/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:05 by archid-           #+#    #+#             */
/*   Updated: 2021/02/16 18:30:39 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "draw.h"

static int		print_usage(void)
{
	ft_putendl_fd("Usage: ./corewar [-dump N] [[-n N] *.cor]", 2);
	return (EXIT_FAILURE);
}

static void		declare_winner(void)
{
	int i;

	i = 0;
	ft_printf("delta %d winner %hhu %hhu\n", g_vm.delta, g_vm.winner, g_vm.nplayers);
	while (i < g_vm.nplayers)
	{
		ft_printf("Player %d %s\n", i, g_vm.gladiators[i].prog_name);
		++i;
	}
	if (g_vm.winner)
		ft_printf("Winner is %{red_fg}%s%{reset}!\n", g_vm.gladiators[g_vm.winner - 1].prog_name);
	else
		ft_putendl("No Winner!!");
}

int				main(int argc, char *argv[])
{
	int ret;


	if ((g_fd = open("vm.log", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0)
		return (EXIT_FAILURE);
	else if (parse_arguments(argc, argv))
	{
		vm_loop();
		declare_winner();
		ret =  EXIT_SUCCESS;
	}
	else
	{
		print_usage();
		ret = EXIT_FAILURE;
	}
	close(g_fd);
    return (ret);
}
