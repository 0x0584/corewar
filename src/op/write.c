/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:50:37 by archid-           #+#    #+#             */
/*   Updated: 2021/02/03 14:58:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

t_u8    st(t_proc proc)
{
	/* g_vm.arena[proc->pc + (g_args[1] + g_args[2]) % IDX_MOD] = g_args[0]; */
}

t_u8    sti(t_proc proc)
{
	/* g_vm.arena[g_args[0]] = g_vm.arena[g_args[0]] = proc->reg[g_args[2]]; */
}
