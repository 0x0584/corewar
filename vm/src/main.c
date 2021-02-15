/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:05 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 12:21:09 by archid-          ###   ########.fr       */
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
	if (g_vm.winner)
		ft_printf("Winner is %s!", g_vm.gladiators[g_vm.winner - 1]);
	else
		ft_putendl("No Winner!!");
}

int				main(int argc, char *argv[])
{
	if ((g_fd = open("vm.log", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0)
		return (EXIT_FAILURE);
	else if (!parse_arguments(argc, argv))
		print_usage();
	else
	{
		vm_loop();
		declare_winner();
	}
	close(g_fd);
    return (EXIT_SUCCESS);
}
