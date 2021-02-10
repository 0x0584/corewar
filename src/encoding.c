/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:44:50 by archid-           #+#    #+#             */
/*   Updated: 2021/02/08 14:38:32 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static t_u8 lookup[] = {
	0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
	0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf,
};

t_u8		bebyte(t_u8 byte)
{
	return ((lookup[byte & 0x0f] << 4) | lookup[byte >> 4]);
}

/* Big Endian Word -- 32-bit */
t_u32		beword(t_u32 word)
{
    return (((word >> 24) & 0xff) | ((word << 8) & 0xff0000) |
			((word >> 8) & 0xff00) | ((word << 24) & 0xff000000));
}

t_u32		get_arg_value(t_proc proc, t_arg arg)
{
	if (encoded(op_encoding(proc, arg)) == T_REG)
		return (proc->reg[proc->op.args.v[arg]]);
	else
		return (proc->op.args.v[arg]);
}

t_arg		op_encoding(t_proc p, t_arg which)
{
	if (which == 0)
		return p->op.encoded.args.arg_1;
	else if (which == 1)
		return p->op.encoded.args.arg_2;
	else if (which == 2)
		return p->op.encoded.args.arg_3;
	else
		return p->op.encoded.args.padding;
}

t_arg		op_meta_encoding(t_proc p, t_arg which)
{
	if (which == 0)
		return p->op.meta.of.arg1_t;
	else if (which == 1)
		return p->op.meta.of.arg2_t;
	else if (which == 2)
		return p->op.meta.of.arg3_t;
	else
		return p->op.encoded.encod;
}

/**
** \brief convert from encoding to argumen type
** \param arg encoding of opeartion
** \return t_arg
*/
t_arg		encoded(t_u8 arg_code)
{
	if (arg_code == REG_CODE)
		return T_REG;
	else if (arg_code == DIR_CODE)
		return T_DIR;
	else if (arg_code == IND_CODE)
		return T_IND;
	else
		return T_PAD;
}