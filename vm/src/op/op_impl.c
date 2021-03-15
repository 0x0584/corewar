/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:02:40 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 08:42:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_impl.h"
#include "op_callback.h"
#include "process.h"

t_op		g_op[op_count] = {
	[op_live] = {.callback = live, 10},
	[op_zjmp] = {.callback = zjmp, 20},

	[op_add] = {.callback = add, 10},
	[op_sub] = {.callback = sub, 10},
	[op_and] = {.callback = and, 6},
	[op_or] = {.callback = or, 6},
	[op_xor] = {.callback = xor, 6},

	[op_ld] = {.callback = ld, 5},
	[op_st] = {.callback = st, 5},
	[op_ldi] = {.callback = ldi, 25},
	[op_sti] = {.callback = sti, 25},

	[op_lld] = {.callback = lld, 10},
	[op_lldi] = {.callback = lldi, 50},

	[op_fork] = {.callback = fork_, 800},
	[op_lfork] = {.callback = lfork, 1000},

	[op_aff] = {.callback = aff, 2},

	[op_nop] = {.callback = nop, 0},
};

void		set_ops(void)
{
	t_op_code	code;

	code = op_nop;
	while (code < op_count)
	{
		ft_memcpy(&g_op[code].info, g_ops + code, sizeof(t_op_info));
		code++;
	}
}
