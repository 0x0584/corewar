/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:54:57 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 17:55:13 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "args.h"
#include "op_impl.h"

t_st				read_reg(t_op *op, const t_arg arg, const char **arg_line)
{
	char			reg[3];
	t_u8			reg_num;

	ft_bzero(reg, 3);
	if (ascii_to_digit(arg_line, reg) && ascii_to_digit(arg_line, reg + 1))
	{
		if (!(reg_num = ft_atoi(reg)) || reg_num > REG_NUMBER)
		{
			ft_dprintf(2, " %{yellow_fg}argument %hhu of operation `%s`"
					   " has invalid register access%{reset}\n",
					   op->info.name, arg);
			return st_fail;
		}
		else
		{
			op->info.args.v[0] = reg_num;
			return st_succ;
		}
	}
	else
	{
		ft_dprintf(2, " %{red_fg}register is invalide%{reset} \n");
		return st_error;
	}
}
