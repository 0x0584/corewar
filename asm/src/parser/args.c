/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:27:56 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:41:30 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

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
	char			c;

	if (ft_isdigit(c = **astr))
	{
		*astr += 1;
		return (*reg = c);
	}
	else if (c && !(ft_isspace(c) || c == deli_comma || is_comment_char(c)))
		return (!ft_dprintf(2, " %{red_fg}register is invalid%{reset} \n"));
	else
		return (true);
}

static t_st		fetch_arg(t_op *op, t_arg arg, const char **arg_line)
{
	if (!arg_line || !*arg_line || !**arg_line)
	{
		ft_dprintf(2, " %{red_fg}end of line while "
		"expecting argument%{reset} \n");
		return (st_error);
	}
	else
		return (read_arg(op, arg, arg_line));
}

t_st			fetch_op_args(t_op *op, const char *args_line)
{
	t_arg			arg;
	t_st			st;

	skip_whitespace(&args_line);
	arg = 0;
	while (arg < op->info.nargs)
		if ((st = fetch_arg(op, arg++, &args_line)))
			return (st);
	skip_whitespace(&args_line);
	if (!*args_line || is_comment_char(*args_line))
		return (st_succ);
	else
	{
		ft_dprintf(2, " %{red_fg}operation arguments exceeded : `%s`%{reset}\n",
					args_line);
		return (st_error);
	}
}
