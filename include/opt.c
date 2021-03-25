/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:42:00 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 11:44:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "opt.h"

static void			match_opt(void *blob, void *arg)
{
	t_opt				*opt;
	t_pair				*pair;

	pair = arg;
	if (!(pair->first && pair->second))
		return ;
	opt = blob;
	if (!ft_strcmp(opt->long_opt, pair->first))
		pair->first = NULL;
	if (*(char *)pair->second == opt->short_opt)
		pair->second = NULL;
}

static bool			duplicate_opt(const char *long_opt, char short_opt)
{
	t_pair pair;

	pair = (t_pair){(char *)long_opt, &short_opt};
	lst_iter_arg(g_opts, true, &pair, match_opt);
	return (!pair.first || !pair.second);
}

bool				opt_str_init(const char *long_opt, char short_opt,
										t_opt_arg_callback parse)
{
	return (opt_init(long_opt, short_opt, true,
					(t_opt_arg){parse, free, str_dump, NULL}));
}

bool				opt_init(const char *long_opt, char short_opt,
								bool has_arg, const t_opt_arg arg)
{
	t_opt				opt;

	if (!g_opts)
		g_opts = lst_alloc(arg.free);
	else if (duplicate_opt(long_opt, short_opt))
		return (false);
	opt.long_opt = long_opt;
	opt.short_opt = short_opt;
	opt.has_arg = has_arg;
	ft_memcpy(&opt.arg, &arg, sizeof(t_opt_arg));
	return (true);
}

bool				opt_match(const char *args[], int at, t_opt *opt)
{
	if (*args[0] != '-')
		return (false);
}

void				opt_cleanup(void)
{
	lst_del(&g_opts);
}

void				str_dump(void *blob)
{
	ft_putendl(blob);
}

const t_opt_arg		g_no_arg;
t_lst				g_opts = NULL;
