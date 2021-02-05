/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:40:20 by archid-           #+#    #+#             */
/*   Updated: 2021/02/03 14:57:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

t_u8    ld(t_proc proc)
{
	/* proc->reg[proc->op.args[1]] = */
	/* 	read_chunk(proc->op, proc->pc + (proc->op.args[0] % IDX_MOD)); */
}

t_u8	lldi(t_proc proc)
{

}

t_u8    ldi(t_proc proc)
{
	/* proc->reg[g_args[2]] = g_vm.arena[g_args[0]] = g_vm.arena[g_args[0]]; */
}

t_u8    lld(t_proc proc)
{
	ft_printf("op lld");

}
