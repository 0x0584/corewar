/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:23:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 16:36:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "op_impl.h"

static char		op_str[MAX_OP_NAME];

static void		find_op(const char *key, void *blob, void *arg)
{
	if (((t_pair *)arg)->first)
		return ;
	else if (!ft_strncmp(key, op_str, MAX_OP_NAME))
	{
		ft_memcpy((void *)&((t_op *)(((t_pair *)arg)->second))->info,
				  blob, sizeof(t_op_info));
		((t_pair *)arg)->first = ((t_pair *)arg)->second;
	}
}

t_st					parse_op(t_op *op, const char *buff)
{
	const char		*spc;
	t_pair			op_fetcher;

	skip_whitespace(&buff);
	if (!*buff)
	{
		ft_dprintf(2, " >> empty line\n");
		return st_fail;
	}
	else if (!(spc = ft_strchr(buff, ' ')))
	{
		ft_dprintf(2, "no arguments are found\n");
		return st_error;
	}

	ft_bzero(op_str, 5);
	ft_strncpy(op_str, buff, min(spc - buff - 1, 4));
	op_fetcher = (t_pair){NULL, op};
	hash_iter_arg(g_op_lookup, &op_fetcher, find_op);
	if (op_fetcher.first)
		return (fetch_op_args(op, spc));
	else
	{
		ft_dprintf(2, "unknow operation `%s`\n", op_str);
		return (st_error);
	}
}

t_st					write_op(t_op *op, t_u8 *buff, t_u16 size)
{

}

t_st					write_prog(t_lst ops, const char *out)
{

}
