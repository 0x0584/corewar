/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:36 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 18:56:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		*g_files[MAX_PLAYERS];

int					count_players(void)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < MAX_PLAYERS)
	{
		if (g_files[i])
			count++;
		i++;
	}
	return (count);
}

static void		champs_intro(void)
{
	int				j;

	ft_dprintf(g_fd, "Introducing contestants...\n");
	j = 0;
	while (j < MAX_PLAYERS)
	{
		if (g_vm.champs[j].prog_size)
			ft_dprintf(g_fd,
						"* Player %d, weighing %hu bytes, \"%s\" (\"%s\") !\n",
						j + 1, g_vm.champs[j].prog_size,
						g_vm.champs[j].prog_name,
						g_vm.champs[j].comment);
		j++;
	}
}

static int		available(void)
{
	int				j;

	j = 0;
	while (j < MAX_PLAYERS)
	{
		if (!g_files[j])
			return (j);
		j++;
	}
	return (j);
}

bool			parse_arguments(int ac, char *av[])
{
	int				i;
	int				j;
	int				n;

	if (ac == 1)
		return (false);
	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-d"))
			g_dump = ft_atoi(av[++i]);
		else if (!ft_strcmp(av[i], "-verbose") || !ft_strcmp(av[i], "-v"))
			g_verbose = ft_atoi(av[++i]);
		else if (!ft_strcmp(av[i], "-aff") || !ft_strcmp(av[i], "-a"))
			g_aff = 1;
		else if (!ft_strcmp(av[i], "-n"))
		{
			if (!((n = ft_atoi(av[++i])) > 0 && n <= MAX_PLAYERS))
				return (false);
			else if (g_files[n - 1])
				return (false);
			g_files[n - 1] = av[i];
		}
		else if (ft_strsuffix(av[i], ".cor"))
		{
			if ((n = available()) == MAX_PLAYERS)
				return (false);
			g_files[n] = av[i];
		}
		i++;
	}
	j = MAX_PLAYERS;
	n = count_players();
	while (j--)
		if (g_files[j])
			if (champ_read(g_files[j], --n, g_vm.champs + j))
				return (false);
	champs_intro();
	return (true);
}

int				g_dump = 0;
int				g_aff = 0;
int				g_verbose = 0;
