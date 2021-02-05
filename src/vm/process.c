/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/04 17:51:09 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

pid_t	g_pid = 1;
t_lst	g_pool = NULL;

t_proc  new_process(t_u8 num, t_u16 at)
{
	t_proc	foo;

	foo = ft_calloc(1, sizeof(struct s_process));
	foo->pid = g_pid++;
	foo->num = num;
	foo->pc = at;
	foo->op = g_ops[op_nop];
	g_pool = lst_push_front_blob(g_pool ? g_pool : lst_alloc(blob_free),
								 foo, sizeof foo, false);
	return (foo);
}

void	process_cleanup()
{

}

t_u16	shift_pc(t_proc p, t_u16 offset)
{
	if (p->op.meta.of.long_op)
		return ((p->pc + offset) % MEM_SIZE);
	else
		return ((p->pc + (offset % IDX_MOD)) % MEM_SIZE);
}

t_u16	pc_shift(t_u16 pc, t_u16 offset, bool long_op)
{
	if (long_op)
		return ((pc + offset) % MEM_SIZE);
	else
		return (((pc + offset) % IDX_MOD) % MEM_SIZE);
}

t_u16	move_pc(t_proc p, t_u16 offset)
{
	return (p->pc = shift_pc(p, offset));
}

t_u16	pc_move(t_u16 *pc, t_u16 offset, bool long_op)
{
	if (!pc)
		return (0);
	else
		return (*pc = pc_shift(*pc, offset, long_op));
}
