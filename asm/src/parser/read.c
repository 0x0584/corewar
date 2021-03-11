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
		op->info.encoded.args.arg_1 = encode(type);
	else if (arg == 1)
		op->info.encoded.args.arg_2 = encode(type);
	else if (arg == 2)
		op->info.encoded.args.arg_3 = encode(type);
	else
	    op->info.encoded.args.padding = T_PAD;
}

static inline t_u8			arg_valid_types(const t_op *op, t_arg arg)
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

static t_st			parse_arg(t_op *op, const t_arg arg, const char **arg_line)
{
	t_arg				type;

	if ((type = decode(op_encoding(&op->info, arg))) & arg_valid_types(op, arg))
	{
		if (type & T_REG)
			return (read_reg(op, arg, arg_line));
		else
			return (parse_arg_value(op, arg, arg_line));
	}
	else
	{
		ft_dprintf(2, " %{red_fg}argument %hhu accept types %04b%{reset}\n", arg, arg_valid_types(op, arg));
		return (st_error);
	}
}

static inline bool	indirect_arg(const char **arg_line)
{
	return (ft_strchr("+-", **arg_line) || ft_isdigit(**arg_line)
				|| **arg_line == deli_label);
}

t_st				read_arg(t_op *op, const t_arg arg, const char **arg_line)
{
	skip_whitespace(arg_line);
	if (**arg_line == deli_reg || **arg_line == deli_dir)
	{
		*arg_line += 1;
		set_encoding(op, arg, **arg_line == deli_reg ? T_REG : T_DIR);
	}
	else if (indirect_arg(arg_line))
		set_encoding(op, arg, T_IND);
	else
	{
		ft_dprintf(2, "%{cyan_fg}%s: arg %d: %{red_fg}unknown argument type%{reset}\n", op->info.name, arg);
		return (st_error);
	}
	return (parse_arg(op, arg, arg_line));
}
