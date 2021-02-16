/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:12:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/16 18:28:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

pid_t		g_pid = 1;
t_lst		g_pool = NULL;

t_proc		new_process(t_u8 player_num, t_pc at)
{
	t_proc	foo;

	foo = ft_calloc(1, sizeof(struct s_process));
	foo->pid = g_pid++;
	foo->num = player_num + 1;
	foo->pc = at;
	foo->reg[1] = -(int)(player_num + 1);
	g_pool = lst_push_front_blob(g_pool ? g_pool : lst_alloc(blob_free),
								 foo, sizeof foo, false);
	return (foo);
}
