/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:55:31 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 18:15:54 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

void    add(t_proc proc)
{
	if (!(proc->reg[proc->op.args.v[2]] = proc->reg[proc->op.args.v[0]] + proc->reg[proc->op.args.v[1]]))
		proc->carry = true;
}

void    sub(t_proc proc)
{
	if (!(proc->reg[proc->op.args.v[2]] = proc->reg[proc->op.args.v[0]] - proc->reg[proc->op.args.v[1]]))
		proc->carry = true;
}

void    and(t_proc proc)
{
	if (!(proc->reg[proc->op.args.v[2]] = proc->reg[proc->op.args.v[0]] & proc->reg[proc->op.args.v[1]]))
		proc->carry = true;
}

void    or(t_proc proc)
{
	if (!(proc->reg[proc->op.args.v[2]] = proc->reg[proc->op.args.v[0]] | proc->reg[proc->op.args.v[1]]))
		proc->carry = true;
}

void    xor(t_proc proc)
{
	if (!(proc->reg[proc->op.args.v[2]] = proc->reg[proc->op.args.v[0]] ^ proc->reg[proc->op.args.v[1]]))
		proc->carry = true;
}
