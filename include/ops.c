#include "op.h"

const t_op_info g_ops[op_count] = {
	[op_live]   = {"live",  .meta.of = {T_DIR,                 T_PAD,                  T_PAD,            LONG_OP, !ENC, !SHORT, !CARRY, T_PAD}, 1},
						                                                                                                            			 
	[op_zjmp]   = {"zjmp",  .meta.of = {T_DIR,                 T_PAD,                  T_PAD,           !LONG_OP, !ENC,  SHORT, !CARRY, T_PAD}, 1},
						                                                                                                            			 
	[op_add]    = {"add",   .meta.of = {T_REG,                 T_REG,                  T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, 3},
	[op_sub]    = {"sub",   .meta.of = {T_REG,                 T_REG,                  T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, 3},
	[op_and]    = {"and",   .meta.of = {T_REG,                 T_REG,                  T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, 3},
	[op_or]     = {"or",    .meta.of = {T_REG,                 T_REG,                  T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, 3},
	[op_xor]    = {"xor",   .meta.of = {T_REG,                 T_REG,                  T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, 3},
						                                                                                                            			 
	[op_ld]     = {"ld",    .meta.of = {T_DIR | T_IND,         T_REG,                  T_PAD,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, 2},
	[op_st]     = {"st",    .meta.of = {T_REG,                 T_IND | T_REG,          T_PAD,           !LONG_OP,  ENC, !SHORT, !CARRY, T_PAD}, 2},
	[op_ldi]    = {"ldi",   .meta.of = {T_REG | T_DIR | T_IND, T_DIR | T_REG,          T_REG,           !LONG_OP,  ENC,  SHORT, !CARRY, T_PAD}, 3},
	[op_sti]    = {"sti",   .meta.of = {T_REG,                 T_REG | T_DIR | T_IND,  T_DIR | T_REG,   !LONG_OP,  ENC,  SHORT, !CARRY, T_PAD}, 3},
	[op_lld]    = {"lld",   .meta.of = {T_DIR | T_IND,         T_REG,                  T_PAD,            LONG_OP,  ENC ,!SHORT,  CARRY, T_PAD}, 2},
	[op_lldi]   = {"lldi",  .meta.of = {T_REG | T_DIR | T_IND, T_DIR | T_REG,          T_REG,            LONG_OP,  ENC,  SHORT,  CARRY, T_PAD}, 3},
						                                                                                                            			 
	[op_fork]   = {"fork",  .meta.of = {T_DIR,                 T_PAD,                  T_PAD,           !LONG_OP, !ENC,  SHORT, !CARRY, T_PAD}, 1},
	[op_lfork]  = {"lfork", .meta.of = {T_DIR,                 T_PAD,                  T_PAD,            LONG_OP, !ENC,  SHORT, !CARRY, T_PAD}, 1},
						                                                                                                            			 
	[op_aff]    = {"aff",   .meta.of = {T_REG,                 T_PAD,                  T_PAD,           !LONG_OP,  ENC, !SHORT, !CARRY, T_PAD}, 1},

	[op_nop]	= {"nop",   .meta.of = {0}}
};
