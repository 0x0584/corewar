/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 19:41:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op_impl.h"

static inline t_u8 encoding_of_arg(t_op_encoding encod, t_u8 which)
{
	if (which == 0)
		return encod.args.arg_1;
	else if (which == 1)
		return encod.args.arg_2;
	else if (which == 2)
		return encod.args.arg_3;
	else
		return encod.args.padding;
}

static union u_chunk read_arg(t_proc p)
{
	union u_chunk	arg;

	arg.val.byte_1 = mem_deref(p);
	arg.val.byte_2 = mem_deref(p, 1);
	if (op->label_size > 2)
	{
		pc++;
		arg.val.byte_3 = *pc++;
		arg.val.byte_4 = *pc;
	}
	return arg.value;
}

static t_u8 set_vm_args(t_u32 *vm_arg, t_proc p, t_u16 pc, t_u8 encod)
{
	// check arg type
	// initialize arg
	if (encod == REG_CODE)
	{
		if (g_vm.arena[pc] >= REG_NUMBER)
			return (false);
		else
		{
			*vm_arg = g_vm.arena[pc];
			return (1);
		}
	}
	else if (encod == DIR_CODE || encod == IND_CODE)
	{
		*vm_arg = read_arg(p);
		return (p->op->label_size);
	}
	else
	{
		return 0;
	}
}

static t_u8	set_args(t_proc p, t_op_encoding encod)
{
	t_u8 nargs;
	t_u8 sz;
	t_u8 tmp;

	sz = 0;
	nargs = p->op->nargs;
	ft_bzero(g_args, sizeof(t_u32) * MAX_ARGS_NUMBER);
	if (!(tmp = set_vm_args(&g_args[0], p, p->pc, encod.args.arg_1)))
		return (false);
	sz += tmp;
	if (!--nargs)
		return (sz);
	else if (!(tmp = set_vm_args(&g_args[1], p,
								 shift_pc(p->pc, sz), encod.args.arg_2)))
		return (false);
	sz += tmp;
	if (!--nargs)
		return (sz);
	else if (!(tmp = set_vm_args(&g_args[2], p,
								 shift_pc(p->pc, sz), encod.args.arg_3)))
		return (false);
	sz += tmp;
	return (sz);
}

static t_u8 skip_size(t_proc p, t_op_encoding encod)
{
	(void)p;
	(void)encod;
	return 0;
}

// check the byte

// match with op args
// move pc after

static inline bool verify_arg_encoding(t_proc p, t_u8 which)
{
	/* return (type & encoding_to_arg_type(encoding_of_arg(encod, which))); */
}

t_st	    vm_decode(t_proc p, t_u8 *offset)
{
    bool			correct;
    t_u8			i;
	t_u16			pc;

	pc = move_pc_offset(p->pc, 1);
	if (p->op->encoded)
	{
        i = 0;
        encod.encoding = g_vm.arena[pc];
        correct = !encod.args.padding;
        while (correct && i < p->op->nargs)
		{
            correct = verify_arg_encoding(p->op->args[i], encod, i);
            i++;
        }
		if (correct)
			*offset = 2 + set_args(p, encod);
		if (correct && !*offset)
			*offset = 2 + skip_size(p, encod);
		return (correct);
    }
	else
	{
		encod.encoding = 0x80;	/* T_DIR */
		*offset = 1 + set_args(p, encod);
		return (true);
    }
}
