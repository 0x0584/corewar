/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:38:34 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 12:22:59 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "process.h"

t_dir		arg_value(t_proc proc, t_arg arg, bool deref)
{
	t_arg type;

	if ((type = decode(op_encoding(&proc->op.info, arg))) == T_IND && deref)
	{
		/* ft_dprintf(g_fd, " ## indirect arg \n"); */
		mem_read_chunk(proc, &proc->op.info.args.c[arg], true, proc->op.info.args.c[arg].short_chunk);
		/* op_dump(&proc->op, true, false); */
		return (proc->op.info.args.v[arg]);
	}
	else
		return (type == T_REG ? (proc->reg[proc->op.info.args.v[arg]])
				: (proc->op.info.args.v[arg]));
}
