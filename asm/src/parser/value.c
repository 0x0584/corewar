/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:58:28 by archid-           #+#    #+#             */
/*   Updated: 2021/02/24 16:03:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

t_st		read_arg_label(t_op *op, t_arg arg, const char **arg_line)
{
	const char *walk;
	char		*label;

	if (**arg_line != LABEL_CHAR)
		return (st_fail);

	*arg_line += 1;
	walk = *arg_line;
	while (*walk && !ft_isspace(*walk) && *walk != deli_comma)
		walk++;

	if (!*walk)
	{
		ft_dprintf(2, " %{yellow_fg}end of line%{reset}\n");
		return st_succ;
	}
	else if (!(ft_isspace(*walk) || *walk == deli_comma || is_comment_char(*walk)))
	{
		ft_dprintf(2, " %{red_fg}invalid separator%{reset}\n");
		return st_error;
	}

	label = ft_strrdup(*arg_line, walk - 1);

	skip_whitespace(&walk);
	if (*walk && !(*walk == deli_comma || is_comment_char(*walk)))
	{
		ft_dprintf(2, "%{red_fg}unexpected delimiter%{reset}\n");
		return st_error;
	}
	else if (is_comment_char(*walk))
	{
		while (*walk)
			walk++;
		*arg_line = walk;
	}
	else
		*arg_line = walk + (*walk == deli_comma);

	walk = label;
	while (*walk)
	{
		if (!ft_strchr(LABEL_CHARS, *walk))
		{
			ft_dprintf(2, "%{red_fg}label contains illigale characters%{reset}\n");
			return st_error;
		}
		walk++;
	}
	op->labels[arg] = label;

	return (st_succ);
}

t_st		read_arg_value_base(t_op *op, t_arg arg, const char **arg_line)
{
	char		*num;
	const char	*walk;

	walk = *arg_line;
	while (ft_isdigit(*walk) && walk - *arg_line < 11)
		walk++;

	if (*walk && !(ft_isspace(*walk) || *walk == deli_comma || is_comment_char(*walk)))
	{
		ft_dprintf(2, "%{red_fg}unexpected delimiter%{reset}\n");
		return (st_error);
	}

	num = ft_strrdup(*arg_line, walk - 1);

	if (is_comment_char(*walk))
	{
		while (*walk)
			walk++;
		*arg_line = walk;
	}
	else
		*arg_line = walk + (*walk == deli_comma);
	op->info.args.v[arg] = ft_atoi(num);

	return st_succ;
}

t_st		parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	if (read_arg_label(op, arg, arg_line))
		return (read_arg_value_base(op, arg, arg_line));
	else
		return (st_succ);
}
