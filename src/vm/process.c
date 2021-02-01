/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 19:36:26 by archid-          ###   ########.fr       */
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
	foo->cycles_to_wait = 0;
	foo->op = NULL;
	g_pool = lst_push_front_blob(g_pool ? g_pool : lst_alloc(blob_free),
								 foo, sizeof foo, false);
	return (foo);
}

t_u16	shift_pc(t_proc p, t_u16 offset)
{
	if (p->op.meta.of.long_op)
		return ((p->pc + offset) % MEM_SIZE);
	else
		return ((p->pc + (offset % IDX_MOD)) % MEM_SIZE);
}

t_u16	move_pc(t_proc p, t_u16 offset)
{
	return (p->pc = shift_pc(p, offset));
}
