/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:40:20 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 18:37:54 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

void    ld(t_proc proc)
{
	t_u8 i;

	if (encoded(proc->op.encoded.args.arg_1) == T_DIR)
		proc->reg[proc->op.args.v[1]] = proc->op.args.v[0];
	else
	{
		i = 0;
// rread from circular memory
	}
}

void	lldi(t_proc proc)
{

}

void    ldi(t_proc proc)
{
	/* proc->reg[g_args[2]] = g_vm.arena[g_args[0]] = g_vm.arena[g_args[0]]; */
}

void    lld(t_proc proc)
{
	ft_printf("op lld");

}
