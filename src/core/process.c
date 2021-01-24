/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/01/24 10:18:10 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

pid_t				g_pid = 0;
t_lst				g_pool = NULL;

static inline int	order_process(const void *foo, const void *bar)
{
	t_proc p1;
	t_proc p2;

	p1 = (void *)foo;
	p2 = (void *)bar;
	if (p1->num != p2->num)
		return p1->num > p2->num;
	else
		return p1->pid < p2->pid;
}

t_proc				new_process(t_u8 num, t_addr at, bool child)
{
	t_proc		foo;

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
