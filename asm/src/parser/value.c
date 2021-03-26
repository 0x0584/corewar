/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:58:28 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:35:10 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static t_st			read_arg_label(t_op *op, t_arg arg, const char **arg_line)
{
	const char				*walk;
	char					*label;

	if (**arg_line != LABEL_CHAR)
		return (st_fail);
	*arg_line += 1;
	walk = *arg_line;
	while (!delimiter(*walk))
		walk++;
	if (valid_label(label = ft_strrdup(*arg_line, walk - 1)))
	{
		free(label);
		return (st_error);
	}
	else
	{
		op->labels[arg] = label;
		return (seek_delimiter(arg_line, walk, op->info.nargs == arg + 1));
	}
}

static const char	*parse_num(const char *walk, bool *overflow)
{
	const char				*ori;
	bool					sign;

	ori = walk;
	sign = false;
	*overflow = false;
	while (*walk && ((!sign && (sign = ft_strchr("+-", *walk) != NULL)) ||
						ft_isdigit(*walk)) && walk - ori < 25)
	{
		if (walk - ori >= 11 + sign)
			*overflow = true;
		walk++;
	}
	return (walk == ori ? NULL : walk);
}

static t_st			read_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	char				*num;
	short				sh;
	int					n;
	const char			*walk;
	bool				overflow;

	if (!(walk = parse_num(*arg_line, &overflow)) || (*walk && !delimiter(*walk)))
		return (st_log(st_error, 2, "op:%s arg:%hhu unexpected delimiter `%c'",
						op->info.name, arg, walk ? *walk : '\0'));
	num = ft_strrdup(*arg_line, walk - 1);
	n = ft_atoi(num);
	sh = n;
	if (overflow || (sh != n && op->info.meta.of.short_chunk))
		st_log(st_fail, 2, "op:%s arg:%hhu warning overflow",
			   op->info.name, arg);
	op->info.args.v[arg] = n;
	free(num);
	return (seek_delimiter(arg_line, walk, op->info.nargs == arg + 1));
}

t_st				parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	t_st					st;

	if ((st = read_arg_label(op, arg, arg_line)) != st_fail)
		return (st);
	else
		return (read_arg_value(op, arg, arg_line));
}
