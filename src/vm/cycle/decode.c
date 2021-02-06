/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 17:26:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

/**
** \brief checked the encoding of arguments for an opeartion held by a process
**
**   `offset` = encoding bye + args
**
** \param p process holding an opeartion
** \param offset the deduced memory footprint of the arguments
** \return
**
**   - `st_succ` if an argument is valid, mostly `T_DIR` and `T_IND`
**   - `st_fail` in case of invalid registery access
**
** \see op.h
*/
t_st					vm_decode(t_proc p, t_u8 *offset)
{
	if (p->op.meta.of.encoded)
	{
		p->op.encoded.encod = shift_pc(p, 1);
		ft_dprintf(g_fd, ">  encoding of %s is %08b\n", p->op.name, p->op.encoded.encod);
		return (read_arg_chunk(p, offset));
	}
	else
	{
		*offset = p->op.encoded.args.arg_1 = T_DIR;
		//
		return (st_succ);
	}
}
