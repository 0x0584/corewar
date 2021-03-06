/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:27:19 by archid-           #+#    #+#             */
/*   Updated: 2021/02/18 18:01:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"


t_pc	pc_shift(t_pc pc, t_pc offset, bool long_op)
{
	t_pc	new_offset;
	t_pc	new_pc;

	if (offset < 0)
		new_offset = long_op ? offset : -(-offset % IDX_MOD);
	else
		new_offset = long_op ? offset : offset % IDX_MOD;
	if ((new_pc = pc + new_offset) < 0)
		return (MEM_SIZE - (-new_pc % MEM_SIZE));
	else
		return (new_pc % MEM_SIZE);
}

t_pc	shift_pc(t_proc p, t_pc offset)
{
	return pc_shift(p->pc, offset, p->op.info.meta.of.long_op);
}

t_pc	move_pc(t_proc p, t_pc offset)
{
	if (!p)
		return (0);
	else
		return (p->pc = shift_pc(p, offset));
}

t_pc	pc_move(t_pc *pc, t_pc offset, bool long_op)
{
	if (!pc)
		return (0);
	else
		return (*pc = pc_shift(*pc, offset, long_op));
}
