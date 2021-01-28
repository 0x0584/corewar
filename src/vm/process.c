/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/01/28 16:00:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

pid_t				g_pid = 1;
t_lst				g_pool = NULL;
t_u32				g_args[3] = {0, 0, 0};

static inline int	order_process(const void *foo, const void *bar)
{
	t_proc p1;
	t_proc p2;

	p1 = (void *)foo;
	p2 = (void *)bar;
	return p1->pid < p2->pid;
}

t_proc				new_process(t_u8 num, t_addr at, bool child)
{
	t_proc		foo;

	ft_printf("addr: %08x value: %08x\n", at, *at);

	foo = ft_calloc(1, sizeof(struct s_process));
	foo->pid = g_pid++;
	foo->num = num;
	foo->pc = at;
	if (!child)
		*foo->reg = num;
	g_pool = lst_insertion_sort(
		lst_push_back_blob(g_pool ? g_pool : lst_alloc(blob_free), foo,
							sizeof foo, false),
		order_process);
	return (foo);
}

t_addr move_pc(t_addr pc, t_s16 offset)
{
	t_u16 diff;

	diff = pc - g_vm.arena + offset;
	if (diff > 0)
		pc += diff % MEM_SIZE;
	else
		pc = g_vm.arena + MEM_SIZE - diff;
	return pc;
}
