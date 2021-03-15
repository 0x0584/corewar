/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:41:40 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 08:33:09 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_callback.h"

void		fork_(t_proc proc)
{
	t_proc	foo;

	foo = new_process(proc->num,
						shift_pc(proc, proc->op.info.args.c[0].short_chunk));
	ft_memcpy(foo->reg, proc->reg, sizeof(t_reg) * (REG_NUMBER + 1));
	foo->carry = proc->carry;
	foo->last_live = proc->last_live;
}

void		lfork(t_proc proc)
{
	fork_(proc);
}
