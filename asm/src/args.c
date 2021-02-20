/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:27:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 16:36:23 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "op_impl.h"

t_u8			arg_valid_types(const t_op *op, t_arg arg)
{
	if (arg == 0)
		return op->info.meta.of.arg1_t;
	else if (arg == 1)
		return op->info.meta.of.arg2_t;
	else if (arg == 2)
		return op->info.meta.of.arg3_t;
	else
		return op->info.meta.of.padding;
}

void			set_op_encoding(t_op *op, t_arg arg, t_u8 type)
{
	if (arg == 0)
		op->info.encoded.args.arg_1 = type;
	else if (arg == 1)
		op->info.encoded.args.arg_2 = type;
	else if (arg == 2)
		op->info.encoded.args.arg_3 = type;
	else
		assert(arg < MAX_ARGS_NUMBER);

}

bool			ascii_to_digit(const char **astr, char *reg)
{
	if (ft_isdigit(*reg = *++astr[0]))
		return (true);
	else
		return (!ft_dprintf(2, " %{red_fg}register is invalide%{reset} \n"));
}

static t_st		fetch_arg(t_op *op, t_arg arg, const char **arg_line)
{

	t_st			st;

	ft_dprintf(2, " reading argument %hhu of operation %s at `%s`\n",
			   op->info.name, arg, arg_line);
	if (!arg_line || !*arg_line || !**arg_line)
	{
		ft_dprintf(2, " %{red_fg}end of line while expecting argument%{reset} \n");
		return st_error;
	}
	else if ((st = read_arg(op, arg, arg_line)))
		return (st);
	else
		return (st_succ);
}

t_st			fetch_op_args(t_op *op, const char *args_line)
{
	t_arg			arg;
	t_st			st;

	arg = 0;
	ft_dprintf(2, " fetching args for `%s`\n", args_line);
	skip_whitespace(&args_line);
	while (arg < op->info.nargs)
		if ((st = fetch_arg(op, arg++, &args_line)))
			return (st);

	if (!*args_line)
		return (st_succ);
	else
	{
		ft_dprintf(2, " operetaion arguments exceeded : `%s`\n", args_line);
		return (st_fail);
	}
}
