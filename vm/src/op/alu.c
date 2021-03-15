/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:55:31 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 08:36:00 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

void		add(t_proc proc)
{
	proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] +
				proc->reg[proc->op.info.args.v[1]];
	proc->carry = !proc->reg[proc->op.info.args.v[2]];
}

void		sub(t_proc proc)
{
	proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] -
				proc->reg[proc->op.info.args.v[1]];
	proc->carry = !proc->reg[proc->op.info.args.v[2]];
}

void		and(t_proc proc)
{
	proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] &
				proc->reg[proc->op.info.args.v[1]];
	proc->carry = !proc->reg[proc->op.info.args.v[2]];
}

void		or(t_proc proc)
{
	proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] |
				proc->reg[proc->op.info.args.v[1]];
	proc->carry = !proc->reg[proc->op.info.args.v[2]];
}

void		xor(t_proc proc)
{
	proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] ^
				proc->reg[proc->op.info.args.v[1]];
	proc->carry = !proc->reg[proc->op.info.args.v[2]];
}
