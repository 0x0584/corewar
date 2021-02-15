/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:36 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 18:38:23 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
		if (player_read(files[j], j + 1, g_vm.gladiators + j))
			return (false);
	return (true);
}
