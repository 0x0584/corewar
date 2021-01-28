/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2021/01/28 16:12:39 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "vm.h"

static t_op		g_ops[] = {
	{
		.op_name = "nop",
		.label_size = 0,
		.encoded = false,
		.callback = op_nop,
		.cycles = 0,
		.nargs = 0,
		.args = {0, 0, 0, 0}
	},
	{"live", 4, false, op_live, 10, 1, {T_DIR}},
	{"ld", 4, true, op_ld, 5, 2, {T_DIR | T_IND, T_REG}},
	{"st", 4, true, op_st, 5, 2, {T_REG, T_IND | T_REG}},
	{"add", 4, true, op_add, 10, 3, {T_REG, T_REG, T_REG}},
	{"sub", 4, true, op_sub, 10, 3, {T_REG, T_REG, T_REG}},
	{"and", 4, true, op_and, 6, 3, {T_REG | T_DIR | T_IND,
										T_REG | T_IND | T_DIR, T_REG}},
	{"or", 4, true, op_or, 6, 3, {T_REG | T_IND | T_DIR,
									T_REG | T_IND | T_DIR, T_REG}},
	{"xor", 4, true, op_xor, 6, 3, {T_REG | T_IND | T_DIR,
										T_REG | T_IND | T_DIR, T_REG}},
	{"zjmp", 2, false, op_zjmp, 20, 1, {T_DIR}},
	{"ldi", 2, true, op_ldi, 25, 3, {T_REG | T_DIR | T_IND,
										T_DIR | T_REG, T_REG}},
	{"sti", 2, true, op_sti, 25, 3, {T_REG, T_REG | T_DIR | T_IND,
										T_DIR | T_REG}},
	{"fork", 2, false, op_fork, 800, 1, {T_DIR}},
	{"lld", 4, true, op_lld, 10, 2, {T_DIR | T_IND, T_REG}},
	{"lldi", 2, true, op_lldi, 50, 3, {T_REG | T_DIR | T_IND,
										T_DIR | T_REG, T_REG}},
	{"lfork", 2, false, op_lfork, 1000, 1, {T_DIR}},
	{"aff", 4, true, op_aff, 2, 1, {T_REG}},
};

static inline t_u8 encoding_of_arg(t_args_encoding encod, t_u8 which)
{
	if (which == 0)
		return encod.args.arg_1;
	else if (which == 1)
		return encod.args.arg_2;
	else if (which == 2)
		return encod.args.arg_3;
	else
	{
		assert(true);
		return encod.args.padding;
	}
}

static inline t_arg_type encoding_to_arg_type(t_u8 encod)
{
	if (encod == REG_CODE)
		return T_REG;
	else if (encod == DIR_CODE)
		return T_DIR;
	else if (encod == IND_CODE)
		return T_IND;
	else
	{
		assert(true);
		return T_PAD;
	}
}

static inline bool verify_arg_encoding(t_arg_type type, t_args_encoding encod, t_u8 which)
{
	return (type & encoding_to_arg_type(encoding_of_arg(encod, which)));
}


static t_u32 read_arg(t_op *op, t_addr pc)
{
	t_args_value	arg;

	arg.val.byte_1 = *pc++;
	arg.val.byte_2 = *pc;
	if (op->label_size > 2)
	{
		pc++;
		arg.val.byte_3 = *pc++;
		arg.val.byte_4 = *pc;
	}
	return arg.value;
}

static t_u8 set_vm_args(t_op *op, t_u32 *vm_arg, t_proc p, t_u8 encod)
{
	t_addr			pc;
	t_u32			arg;

	pc = p->pc;
	// check arg type
	// initialize arg
	if (encod == REG_CODE)
	{
		*vm_arg = p->reg[*pc];
		return 1;
	}
	else if (encod == DIR_CODE || encod == IND_CODE)
	{
		arg = read_arg(op, p->pc);
		*vm_arg = (encod == DIR_CODE ? arg : read_arg(op, move_pc(p->pc, arg)));
		return op->label_size;
	}
	else
	{
		assert(true);
		return 0;
	}
}

static t_u8	set_args(t_op *op, t_proc p, t_args_encoding encod)
{
	t_u8 nargs;
	t_u8 sz;

	nargs = op->nargs;
	sz = set_vm_args(op, &g_args[0], p, encod.args.arg_1);
	if (!--nargs)
		return sz;
	sz += set_vm_args(op, &g_args[1], p, encod.args.arg_2);
	if (!--nargs)
		return sz;
	sz += set_vm_args(op, &g_args[2], p, encod.args.arg_3);
	return sz;
}

static void	op_do_callback()
{

}

// check the byte

// match with op args
// move pc after

static bool	check_encoding(t_proc p)
{
	t_args_encoding encod;
	bool			flag;
	t_u8			i;
	t_op			*op;

	if (*p->pc >= sizeof g_ops / sizeof *g_ops)
		return (!ft_dprintf(2, "%02x is not an operation\n", *p->pc));

	op = &g_ops[*p->pc++];
	encod.encoding = *p->pc++;

	ft_printf("%{cyan_fg}1:%02b 2:%02b 3:%02b pad:%02b%{reset}\n",
			  encod.args.arg_1, encod.args.arg_2, encod.args.arg_3,
			  encod.args.padding);

	i = 0;
	flag = false;
	while (!flag && i < op->nargs)
	{
		flag = verify_arg_encoding(op->args[i], encod, i);
		i++;
	}
	return (!flag && !encod.args.padding ? set_args(op, p, encod) : 0);
}

void	op_callback(void *proc)
{
	t_proc	p;
	t_u8	instr_offset;

	p = proc;
	if ((instr_offset = check_encoding(proc)))
	{
		ft_printf("encoding is correct");
		op_do_callback();
		p->pc = move_pc(p->pc, instr_offset);
	}
	else
	{
		ft_printf("skip");
	}
}

void    op_live(t_proc procc)
{
	ft_printf("op live");
}

void    op_aff(t_proc proc)
{
	ft_printf("op aff");
}

void    op_lldi(t_proc proc)
{
	ft_printf("op lldi");
}

void    op_zjmp(t_proc proc)
{
	ft_printf("op zjmp");
}

void   	op_nop(t_proc proc)
{
	ft_printf("op nop");
}
