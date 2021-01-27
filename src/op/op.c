/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2021/01/27 14:26:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "vm.h"

static t_op	ops[] = {
	{"nop", op_nop, 0, 0, {0}},
	{"live", op_live, 10, 1, {T_DIR}},
	{"ld", op_ld, 5, 2, {T_DIR | T_IND, T_REG}},
	{"st", op_st, 5, 2, {T_REG, T_IND | T_REG}},
	{"add", op_add, 10, 3, {T_REG, T_REG, T_REG}},
	{"sub", op_sub, 10, 3, {T_REG, T_REG, T_REG}},
	{"and", op_and, 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
	{"or", op_or, 6, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	{"xor", op_xor, 6, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	{"zjmp", op_zjmp, 20, 1, {T_DIR}},
	{"ldi", op_ldi, 25, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"sti", op_sti, 25, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	{"fork", op_fork, 800, 1, {T_DIR}},
	{"lld", op_lld, 10, 2, {T_DIR | T_IND, T_REG}},
	{"lldi", op_lldi, 50, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"lfork", op_lfork, 1000, 1, {T_DIR}},
	{"aff", op_aff, 2, 1, {T_REG}},
};

// check the byte

// match with op args
// move pc after

static bool	check_args(t_op *op, t_addr args)
{
	t_u8			i;
	t_args_encoding encod;

	ft_printf("little: %08b big: %08b\n", *args, bebyte(*args));
	encod.encoding = *args;
	i = 0;
	while (i < op->nargs)
	{

		if (which_arg[encod](op->args[i], encod))
		{

		}
		else
		{
			/* skip op */
			break;
		}
		i++;
	}
	return (true);
}

void	op_callback(void *proc)
{
	t_proc	p;
	t_op	*op;

	p = proc;
	if (*p->pc >= sizeof ops / sizeof *ops) {
		ft_dprintf(2, "%02x is not an operation\n", *p->pc);
		return ;
	}
	op = &ops[*p->pc++];
	if (check_args(op, p->pc))
	{

	}
	else
	{

	}
}

void    op_live(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c)
{

}

void    op_aff(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c)
{

}

void    op_lldi(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c)
{

}

void    op_zjmp(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c)
{

}

void   	op_nop(t_proc proc, t_u32 *a, t_u32 *b, t_u32 *c)
{

}
