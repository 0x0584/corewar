/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:44:50 by archid-           #+#    #+#             */
/*   Updated: 2021/02/04 11:46:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "process.h"

t_u8		op_encoding(t_proc p, t_arg which)
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

t_u8		op_meta_encoding(t_proc p, t_arg which)
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
t_arg		encoded(t_u8 arg)
{
	if (arg == REG_CODE)
		return T_REG;
	else if (arg == DIR_CODE)
		return T_DIR;
	else if (arg == IND_CODE)
		return T_IND;
	else
		return T_PAD;
}
