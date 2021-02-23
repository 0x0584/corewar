/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:54:57 by archid-           #+#    #+#             */
/*   Updated: 2021/02/23 17:48:12 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "args.h"
#include "op_impl.h"

static t_u8			valid_register_number(const char **arg_line)
{
	char			reg[3];
	t_u8			reg_num;

	ft_bzero(reg, 3);
	if  (!(ascii_to_digit(arg_line, reg) && ascii_to_digit(arg_line, reg + 1)) ||
			!(ft_isspace(**arg_line) || (**arg_line == deli_comma)) ||
			!(reg_num = ft_atoi(reg)) || reg_num > REG_NUMBER)
		return 0;
	else
		return reg_num;
}

t_st				read_reg(t_op *op, const t_arg arg, const char **arg_line)
{
	t_u8			reg_num;

	if (!(reg_num = valid_register_number(arg_line)))
	{
		ft_dprintf(2, " %{red_fg}argument %hhu of operation `%s` has invalid register access%{reset}\n",
				   op->info.name, arg);
		return (st_error);
	}
	skip_whitespace(arg_line);
	if (**arg_line != deli_comma)
	{
		ft_dprintf(2, " %{red_fg}argument %hhu of operation `%s` has invalid register access%{reset}\n",
				   op->info.name, arg);
		return (st_error);
	}
	else
	{
		*arg_line += 1;
		op->info.args.v[0] = reg_num;
		return (st_succ);
	}
}
