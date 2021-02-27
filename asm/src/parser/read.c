/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:59:08 by archid-           #+#    #+#             */
/*   Updated: 2021/02/26 10:09:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static inline void	set_encoding(t_op *op, t_arg arg, t_u8 type)
{
	if (arg == 0)
		op->info.encoded.args.arg_1 = uncode(type);
	else if (arg == 1)
		op->info.encoded.args.arg_2 = uncode(type);
	else if (arg == 2)
		op->info.encoded.args.arg_3 = uncode(type);
	else
	    op->info.encoded.args.padding = T_PAD;
}

t_st				read_arg(t_op *op, const t_arg arg, const char **arg_line)
{
	skip_whitespace(arg_line);

	if (**arg_line == deli_reg)
	{
		set_encoding(op, arg, T_REG);
		*arg_line += 1;
		return read_reg(op, arg, arg_line);
	}
	else if (**arg_line == DIRECT_CHAR)
	{
		*arg_line += 1;
		set_encoding(op, arg, T_DIR);
	}
	else if (ft_strchr("+-", **arg_line) || ft_isdigit(**arg_line) || **arg_line == LABEL_CHAR)
		set_encoding(op, arg, T_IND);
	else
	{
		ft_dprintf(2, "%{cyan_fg}%s: arg %d: %{red_fg}unknown argument type%{reset}",
				   op->info.name, arg);
		return (st_error);
	}

	if (op_encoding(&op->info, arg) | arg_valid_types(op, arg))
		return (parse_arg_value(op, arg, arg_line));
	else
	{
		ft_dprintf(2, " %{red_fg}argument %hhu accept types %04b%{reset}\n",
				   arg, arg_valid_types(op, arg));
		return (st_error);
	}
}
