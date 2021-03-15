/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:52:33 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 11:15:06 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

const t_op_info g_ops[op_count] = {
	[op_live] = {op_live, "live",
		.meta.of = {T_DIR, T_PAD, T_PAD, LONG_OP, !ENC, !SHORT, !CARRY, T_PAD},
		1},

	[op_zjmp] = {op_zjmp, "zjmp",
		.meta.of = {T_DIR, T_PAD, T_PAD, !LONG_OP, !ENC, SHORT, !CARRY, T_PAD},
		1},

	[op_add] = {op_add, "add",
		.meta.of = {T_REG, T_REG, T_REG, !LONG_OP, ENC, !SHORT, CARRY, T_PAD},
		3},
	[op_sub] = {op_sub, "sub",
		.meta.of = {T_REG, T_REG, T_REG, !LONG_OP, ENC, !SHORT, CARRY, T_PAD},
		3},
	[op_and] = {op_and, "and",
		.meta.of = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG,
			!LONG_OP, ENC, !SHORT, CARRY, T_PAD},
		3},
	[op_or] = {op_or, "or",
		.meta.of = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG,
			!LONG_OP, ENC, !SHORT, CARRY, T_PAD},
		3},
	[op_xor] = {op_xor, "xor",
		.meta.of = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG,
			!LONG_OP, ENC, !SHORT, CARRY, T_PAD},
		3},

	[op_ld] = {op_ld, "ld",
		.meta.of = {T_DIR | T_IND, T_REG, T_PAD, !LONG_OP, ENC, !SHORT,
			CARRY, T_PAD},
		2},
	[op_st] = {op_st, "st",
		.meta.of = {T_REG, T_IND | T_REG, T_PAD, !LONG_OP, ENC, !SHORT,
			!CARRY, T_PAD},
		2},
	[op_ldi] = {op_ldi, "ldi",
		.meta.of = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG,
			!LONG_OP, ENC, SHORT, !CARRY, T_PAD},
		3},
	[op_sti] = {op_sti, "sti",
		.meta.of = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG,
			!LONG_OP, ENC, SHORT, !CARRY, T_PAD},
		3},
	[op_lld] = {op_lld, "lld",
		.meta.of = {T_DIR | T_IND, T_REG, T_PAD, LONG_OP, ENC, !SHORT,
			CARRY, T_PAD},
		2},
	[op_lldi] = {op_lld, "lldi",
		.meta.of = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG,
			LONG_OP, ENC, SHORT, CARRY, T_PAD},
		3},

	[op_fork] = {op_fork, "fork",
		.meta.of = {T_DIR, T_PAD, T_PAD, !LONG_OP, !ENC, SHORT, !CARRY,
			T_PAD},
		1},
	[op_lfork] = {op_lfork, "lfork",
		.meta.of = {T_DIR, T_PAD, T_PAD, LONG_OP, !ENC, SHORT, !CARRY,
			T_PAD},
		1},

	[op_aff] = {op_aff, "aff",
		.meta.of = {T_REG, T_PAD, T_PAD, !LONG_OP, ENC, !SHORT, !CARRY,
			T_PAD},
		1},

	[op_nop] = {op_nop, "nop", .meta.of = {0}}
};
