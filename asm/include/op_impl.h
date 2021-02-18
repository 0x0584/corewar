/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:06:01 by archid-           #+#    #+#             */
/*   Updated: 2021/02/18 16:03:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_IMPL_H
# define OP_IMPL_H

# include "op.h"

# define ARG_BASE_BIN		1
# define ARG_BASE_OCT		2
# define ARG_BASE_DEC		4
# define ARG_BASE_HEX		8

typedef enum	e_op_delimiters
{
	deli_eol			= '\0',

	deli_comment		= COMMENT_CHAR,
	deli_asm_comment	= ';',

	deli_comma			= SEPARATOR_CHAR,
	deli_label	 		= LABEL_CHAR,
	deli_dir	 		= DIRECT_CHAR,
	deli_reg			= 'r',

	deli_bin	 		= 'b',
	deli_octa	 		= '0',
	deli_hexa	 		= 'x',

	deli_unknown		= -1,
}				t_deli;

bool			delimiter(t_deli d);

typedef union	u_args_base
{
	t_u16	mask;
	struct		s_bases
	{
		t_u8	arg1:4;
		t_u8	arg2:4;
		t_u8	arg3:4;
		t_u8	padding:4;
	} base;
}				t_args_base;

typedef struct	s_operation
{
	t_op_info		info;
	t_u16			addr;
}				t_op;

extern t_hash	g_labels;
extern t_u16	g_max_op_length;

#endif
