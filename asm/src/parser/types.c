/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:54:57 by archid-           #+#    #+#             */
/*   Updated: 2021/02/26 10:09:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

t_st				valid_label(const char *label)
{
	while (*label)
	{
		if (!ft_strchr(LABEL_CHARS, *label))
		{
			ft_dprintf(2, "%{red_fg}label contains illigale characters%{reset}\n");
			return st_error;
		}
		label++;
	}
	return st_succ;
}

static t_u8			valid_register_number(const char **arg_line)
{
	char			reg[3];
	t_u8			reg_num;

	ft_bzero(reg, 3);
	if	(!(ascii_to_digit(arg_line, reg) && ascii_to_digit(arg_line, reg + 1)) ||
		 !delimiter(**arg_line) || !(reg_num = ft_atoi(reg)) || reg_num > REG_NUMBER)
		return (0);
	else
		return (reg_num);
}

t_st				read_reg(t_op *op, const t_arg arg, const char **arg_line)
{
	t_u8			reg_num;

	if (!(reg_num = valid_register_number(arg_line)))
	{
		ft_dprintf(2, " %{red_fg}argument %hhu of operation `%s` has invalid register access%{reset}\n",
				   arg, op->info.name);
		return (st_error);
	}
	skip_whitespace(arg_line);
	if (delimiter(**arg_line))
	{
		if (**arg_line)
			*arg_line += 1;
		op->info.args.v[arg] = reg_num;
		return (st_succ);
	}
	else
	{
		ft_dprintf(2, " %{red_fg}argument %hhu of operation `%s` has invalid register access%{reset}\n",
				   arg, op->info.name);
		return (st_error);
	}
}
