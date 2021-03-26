/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:36 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 11:36:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static const char	*g_files[MAX_PLAYERS];

static bool			g_set_with_flag[] = {
	false, false, false, false
};

static void			champs_intro(void)
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

static t_st			match_dump(int *i, const int count, const char *av[])
{
	if (*i + 1 < count)
	{
		*i += 1;
		g_dump = ft_atoi(av[*i]);
		return (st_succ);
	}
	else
		return (st_log(st_error, 2, "end of arguments"));
}

static bool			match_verbose(int *i, const int count, const char *av[])
{
	if (*i + 1 < count)
	{
		*i += 1;
		g_verbose = ft_atoi(av[*i]);
		return (st_succ);
	}
	else
		return (st_log(st_error, 2, "end of arguments"));
}

static t_st			set_number(const char *str, int *num)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
	{
		*num = ft_atoi(str);
		return (st_succ);
	}
	else
		return (st_log(st_error, 2, "argument of `-n` is not a number"));
}

static t_st			match_player(int *i, const int count, const char *av[])
{
	int					n;
	int					available;
	bool				has_num;

	available = 0;
	n = 0;
	has_num = false;
	if ((has_num = !ft_strcmp(av[*i], "-n")))
	{
		if (*i + 1 < count)
		{
			if (set_number(av[*i += 1], &n))
				return st_error;
			g_set_with_flag[n -= 1] = true;
			if (*i + 1 < count)
				*i += 1;
			else
				return (st_log(st_error, 2, "end of arguments"));
		}
		else
			return (st_log(st_error, 2, "end of arguments"));
	}
	while (g_files[available] && available < MAX_PLAYERS)
		available++;
	if (n < 0 || n >= MAX_PLAYERS || available == MAX_PLAYERS)
		return (st_log(st_error, 2, available == MAX_PLAYERS ? "max players reached"
										: "number is invalid %d", n));
	else if (!ft_strsuffix(av[*i], ".cor"))
		return (st_log(st_error, 2, "%s does not support %s file format",
						av[0], av[*i]));
	if (has_num)
	{
		if (g_files[n] && g_set_with_flag[available])
			return (st_log(st_error, 2, "there is already a %d player", n));
		else
			g_files[available] = g_files[n];
	}
	else
		n = available;
	g_files[n] = av[*i];
	g_n_players++;
	return st_succ;
}

static int			match_option(int i, const int count, const char *av[])
{
	if ((!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-d")))
		return (match_dump(&i, count, av) ? false : i);
	else if ((!ft_strcmp(av[i], "-verbose") || !ft_strcmp(av[i], "-v")))
		return (match_verbose(&i, count, av) ? false : i);
	else if (!ft_strcmp(av[i], "-aff") || !ft_strcmp(av[i], "-a"))
		g_aff = 1;
	else if (match_player(&i, count, av))
		return (false);
	return i;
}

static bool champs_read(void)
{
	int champ;

	champ = MAX_PLAYERS;
	while (champ--)
	{
		if (g_files[champ])
			if (champ_read(g_files[champ], champ, g_vm.champs + champ))
				return (false);
	}
	return (true);
}

bool			parse_arguments(int ac, const char *av[])
{
	int				arg;

	if (ac == 1)
		return (false);
	arg = 1;
	while (arg < ac)
	{
		if (!(arg = match_option(arg, ac, av)))
			return (false);
		arg++;
	}
	if (!champs_read())
		return (false);
	champs_intro();
	return (true);
}

int				g_dump;
int				g_aff;
int				g_verbose;
int				g_n_players;
