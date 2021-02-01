/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:02:40 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 17:04:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_impl.h"
#include "builtin.h"

/**
 ** \brief using a single Byte, we shall indicate which argument
 ** as well as its expected type(s) and encode it within the meta
 **
 ** \param meta operation meta information
 ** \param arg_n_meta argument and it's meta data
 **
 ** \return the meta with the argument encoded
 */
static inline t_u16 set_meta_arg(t_u8 arg_n_meta)
{
	/* return ((arg_n_meta & 0xf0) << (arg_n_meta & 0x0f)) << 2)); */
}

t_op		g_ops[op_count] = {
	[op_nop] = {
		.op_name = "nop",  .label_size = 0, .callback = nop,
		.cycles = 0,	   .nargs = 0,		.args = {0, 0, 0, 0},
			  .long_op = mod_op, .encoded = not_enc_op,
	},
	[op_live] =	 {"live",		live,     4,			10,		1,	 {T_DIR},												mod_op,		not_enc_op},
	[op_ld] =	 {"ld",			ld,	      4,			5,		2,	 {T_DIR | T_IND, T_REG},								mod_op,		enc_op},
	[op_st] =	 {"st",			st,	      4,			5,		2,	 {T_REG, T_IND | T_REG},								mod_op,		enc_op},
	[op_add] =	 {"add",		add,      4,			10,		3,	 {T_REG, T_REG, T_REG},									mod_op,		enc_op},
	[op_sub] =	 {"sub",		sub,      4,			10,		3,	 {T_REG, T_REG, T_REG},									mod_op,		enc_op},
	[op_and] =	 {"and",		and,      4,			6,		3,	 {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	mod_op,		enc_op},
	[op_or] =	 {"or",			or,	      4,			6,		3,	 {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	mod_op,		enc_op},
	[op_xor] =	 {"xor",		xor,      4,			6,		3,	 {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	mod_op,		enc_op},
	[op_zjmp] =	 {"zjmp",		zjmp,     2,			20,		1,	 {T_DIR},												mod_op,		not_enc_op},
	[op_ldi] =	 {"ldi",		ldi,      2,			25,		3,	 {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			mod_op,		enc_op},
	[op_sti] =	 {"sti",		sti,      2,			25,		3,	 {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			mod_op,		enc_op},
	[op_fork] =	 {"fork",		fork_,     2,			800,	1,	 {T_DIR},												long_op,	not_enc_op},
	[op_lld] =	 {"lld",		lld,       4,			10,		2,	 {T_DIR | T_IND, T_REG},								long_op,	enc_op},
	[op_lldi] =	 {"lldi",		lldi,      2,			50,		3,	 {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			long_op,	enc_op},
	[op_lfork] = {"lfork",		lfork,     2,			1000,	1,	 {T_DIR},												long_op,	not_enc_op},
	[op_aff] =	 {"aff",		aff,      4,			2,		1,	 {T_REG},												long_op,	enc_op},
};
