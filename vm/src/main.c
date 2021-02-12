/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:05 by archid-           #+#    #+#             */
/*   Updated: 2021/02/12 19:15:41 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "draw.h"

static int	print_usage(void)
{
	ft_putendl_fd("Usage: ./corewar [-dump N] [[-n N] *.cor]", 2);
	return (EXIT_FAILURE);
}

int			main(int argc, char *argv[])
{
	if ((g_fd = open("vm.log", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0)
		return (EXIT_FAILURE);
	else if (parse_arguments(argc, argv))
		vm_loop();
	else
		return (print_usage());
	close(g_fd);
    return (EXIT_SUCCESS);
}
