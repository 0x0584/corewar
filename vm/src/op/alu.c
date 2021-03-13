/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:55:31 by archid-           #+#    #+#             */
/*   Updated: 2021/03/13 17:00:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

void    add(t_proc proc)
{
	proc->carry =!(proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] + proc->reg[proc->op.info.args.v[1]]);
}

void    sub(t_proc proc)
{
	proc->carry = !(proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] - proc->reg[proc->op.info.args.v[1]]);
}

void    and(t_proc proc)
{
	proc->carry = !(proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] & proc->reg[proc->op.info.args.v[1]]);
}

void    or(t_proc proc)
{
	proc->carry = !(proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] | proc->reg[proc->op.info.args.v[1]]);
}

void    xor(t_proc proc)
{
	proc->carry = !(proc->reg[proc->op.info.args.v[2]] = proc->reg[proc->op.info.args.v[0]] ^ proc->reg[proc->op.info.args.v[1]]);
}
