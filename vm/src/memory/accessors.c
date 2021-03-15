/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:07:31 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 10:07:45 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "memory.h"
#include "process.h"

t_u8	mem_deref(t_proc p, t_pc offset)
{
	return (g_vm.arena[shift_pc(p, offset)]);
}

t_u8	mem_at(t_proc p)
{
	return (mem_deref(p, 0));
}

t_u8	at_mem(t_pc pc)
{
	return (g_vm.arena[pc]);
}
