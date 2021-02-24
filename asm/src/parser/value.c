/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:58:28 by archid-           #+#    #+#             */
/*   Updated: 2021/02/24 17:35:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static t_st		seek_delimiter(const char **arg_line, const char *walk)
{
	skip_whitespace(&walk);
	if (*walk && *walk != deli_comma)
	{
		ft_dprintf(2, "%{red_fg}unexpected delimiter%{reset}\n");
		return st_error;
	}
	else
	{
		*arg_line = walk + (*walk == deli_comma);
		return st_succ;
	}
}

static t_st		read_arg_label(t_op *op, t_arg arg, const char **arg_line)
{
	const char *walk;
	char		*label;

	if (**arg_line != LABEL_CHAR)
		return (st_fail);
	*arg_line += 1;
	walk = *arg_line;
	while (!delimiter(*walk))
		walk++;
	if (valid_label(label = ft_strrdup(*arg_line, walk - 1)))
	{
		free(label);
		return st_error;
	}
	else
	{
		op->labels[arg] = label;
		return (seek_delimiter(arg_line, walk));
	}
}

static t_st		read_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	char		*num;
	short		sh;
	int			n;
	const char	*walk;

	walk = *arg_line;
	while (ft_isdigit(*walk) && walk - *arg_line < 11)
		walk++;
	if (*walk && !delimiter(*walk))
	{
		ft_dprintf(2, "%{red_fg}unexpected delimiter%{reset}\n");
		return (st_error);
	}
	num = ft_strrdup(*arg_line, walk - 1);
	n = ft_atoi(num);
	sh = n;
	if (sh != n && op->info.meta.of.short_chunk)
	{
		ft_dprintf(2, "%{red_fg}warnign overflow of arg %hhu in op %s %{reset}\n",
				   arg, op->info.name);
	}
	op->info.args.v[arg] = n;
	free(num);
	return seek_delimiter(arg_line, walk);
}

t_st			parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	if (read_arg_label(op, arg, arg_line))
		return (read_arg_value(op, arg, arg_line));
	else
		return (st_succ);
}
