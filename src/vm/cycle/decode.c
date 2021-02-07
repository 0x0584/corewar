/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/07 11:18:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

t_st					vm_decode(t_proc p, t_u8 *offset)
{
	if (p->op.meta.of.encoded)
	{
		p->op.encoded.encod = shift_pc(p, 1);
		ft_dprintf(g_fd, ">	 encoding of %s is %08b\n", p->op.name, p->op.encoded.encod);
		return (read_arg_chunk(p, offset));
	}
	else
	{
		*offset = p->op.encoded.args.arg_1 = T_DIR;
		//
		return (st_succ);
	}
}
