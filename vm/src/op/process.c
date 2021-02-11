/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:41:40 by archid-           #+#    #+#             */
/*   Updated: 2021/02/11 18:41:31 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void    fork_(t_proc proc)
{
	t_proc	foo;

	foo = new_process(proc->num, shift_pc(proc, proc->op.args.v[0]));
	ft_memcpy(foo->reg, proc->reg, sizeof(t_u32) * (REG_NUMBER + 1));
	foo->carry = proc->carry;
}

void    lfork(t_proc proc)
{
	// cleanup only if exectude on op
	fork_(proc);
}
