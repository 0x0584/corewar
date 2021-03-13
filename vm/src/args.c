/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:36 by archid-           #+#    #+#             */
/*   Updated: 2021/03/13 11:15:45 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "flags.h"

static char		*files[MAX_PLAYERS];

t_st			parse_arguments(int ac, char *av[])
{
	int				i;
	int				j;

	if (ac == 1)
		return (false);
	/* else */
	/* 	parse_flags(ac, av); */

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
		if (champ_read(files[j], j, g_vm.champs + j))
			return (false);
	ft_dprintf(g_fd, "Introducing contestants...\n");
	j = 0;
	while (j < g_vm.nplayers)
	{
		ft_dprintf(g_fd, "* Player %d, weighing %hu bytes, \"%s\" (\"%s\") !\n",
				  j + 1, g_vm.champs[j].prog_size,
				  g_vm.champs[j].prog_name,
				  g_vm.champs[j].comment);
		j++;
	}
	return (true);
}
