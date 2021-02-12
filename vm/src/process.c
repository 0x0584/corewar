/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/12 11:14:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

pid_t	g_pid = 1;
t_lst	g_pool = NULL;

t_proc	new_process(t_u8 player_num, t_pc at)
{
	t_proc	foo;

	foo = ft_calloc(1, sizeof(struct s_process));
	foo->pid = g_pid++;
	foo->num = player_num;
	foo->pc = at;
	g_pool = lst_push_front_blob(g_pool ? g_pool : lst_alloc(blob_free),
								 foo, sizeof foo, false);
	return (foo);
}

void	reset_alive(void *proc)
{
	(*(t_proc)proc).alive = false;
}

void	process_cleanup()
{
	g_vm.cycles++;
	lst_iter(g_pool, true, reset_alive);

// check cyle to die
}

t_u16	shift_pc(t_proc p, t_pc offset)
{
	if (p->op.meta.of.long_op)
		return ((p->pc + offset) % MEM_SIZE);
	else
		return ((p->pc + (offset % IDX_MOD)) % MEM_SIZE);
}

t_u16	pc_shift(t_pc pc, t_pc offset, bool long_op)
{
	if (long_op)
		return ((pc + offset) % MEM_SIZE);
	else
		return ((pc + (offset % IDX_MOD)) % MEM_SIZE);
}

t_u16	move_pc(t_proc p, t_pc offset)
{
	return (p->pc = shift_pc(p, offset));
}

t_u16	pc_move(t_pc *pc, t_pc offset, bool long_op)
{
	if (!pc)
		return (0);
	else
		return (*pc = pc_shift(*pc, offset, long_op));
}
