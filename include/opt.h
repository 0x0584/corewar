/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:43:02 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 11:44:28 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H

# include "lst.h"

typedef struct s_opt		t_opt;
typedef struct s_opt_arg	t_opt_arg;

typedef bool	(*t_opt_arg_callback)(const char *args[], int at, t_opt *opt);
typedef	void	(*t_opt_arg_free)(void *arg);
typedef	void	(*t_opt_arg_dump)(void *arg);

struct			s_opt_arg
{
	const t_opt_arg_callback		parse;
	const t_opt_arg_free			free;
	const t_opt_arg_dump			dump;
	void							*value;
};

struct			s_opt
{
	const char				*long_opt;
	char					short_opt;

	bool					has_arg;
	t_opt_arg				arg;
};

void			str_dump(void *blob);

bool			opt_str_init(const char *long_opt, char short_opt,
								t_opt_arg_callback parse);
void			opt_cleanup(void);
bool			opt_init(const char *long_opt, char short_opt,
								bool has_arg, const t_opt_arg arg);
bool			opt_match(const char *args[], int at, t_opt *opt);

# define OPT_NO_ARG	g_no_arg

extern const t_opt_arg	g_no_arg;
extern t_lst			g_opts;

#endif
