/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:12:50 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 10:51:00 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "const.h"

# include "hash.h"
# include "lst.h"

# define LONG_OP						true
# define ENC							true
# define SHORT							true
# define CARRY							true

typedef enum				e_operation
{
	op_nop,
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff,

	op_count
}							t_op_code;

typedef union				u_op_meta
{
	t_u16		meta;
	struct					s_meta
	{
		t_u8		arg1_t:4;
		t_u8		arg2_t:4;
		t_u8		arg3_t:4;
		bool		long_op:1;
		bool		encoded:1;
		bool		short_chunk:1;
		bool		carry:1;
		t_u8		padding:4;
	}			of;
}							t_op_meta;

typedef t_u8				t_arg;
typedef t_u8				t_byte;
typedef t_s16				t_ind;
typedef t_s32				t_dir;

typedef union				u_op_encoding
{
	t_u8		encod;
	struct					s_op_encoding
	{
		t_u8		padding:2;
		t_u8		arg_3:2;
		t_u8		arg_2:2;
		t_u8		arg_1:2;
	}			args;
}							t_op_encoding;

typedef union				u_blob
{
	t_dir		v[MAX_ARGS_NUMBER];

	union					u_chunk
	{
		struct				s_fragment
		{
			t_u8		byte_1;
			t_u8		byte_2;
			t_u8		byte_3;
			t_u8		byte_4;
		}			val;
		t_dir		chunk;
		t_ind		short_chunk;
	}			c[MAX_ARGS_NUMBER];
}							t_blob;

typedef struct				s_op_info
{
	const t_op_code		code;
	const char			*name;
	t_op_meta			meta;
	const t_u8			nargs;
	t_blob				args;
	t_op_encoding		encoded;
	const char			*doc;
}							t_op_info;

t_arg						op_encoding(const t_op_info *info, t_arg which);
t_arg						op_meta_encoding(const t_op_info *info,
												t_arg which);
t_arg						decode(t_u8 arg_code);
t_u8						encode(t_arg arg_type);

extern const t_op_info		g_ops[op_count];

#endif
