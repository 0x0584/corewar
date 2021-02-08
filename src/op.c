/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:02:40 by archid-           #+#    #+#             */
/*   Updated: 2021/02/07 11:56:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_impl.h"
#include "builtin.h"
#include "process.h"

#define LONG_OP							true
#define ENC								true
#define SHORT							true
#define CARRY							true

void		set_nop(t_proc p)
{
	ft_memcpy(&p->op, &g_ops[op_nop], sizeof(t_op));
}

t_op		g_ops[op_count] = {
	[op_live]	=	 {"live",       live,	10,	   1,    .meta.of = {T_DIR,				    T_PAD,				    T_PAD,		 	  LONG_OP, !ENC, !SHORT, !CARRY, T_PAD}, "annouce player asnumber of first argument as alive, forwhich the process remaine on cycle by the vm"},

	[op_zjmp]	=	 {"zjmp",		zjmp,	20,	   1, 	 .meta.of = {T_DIR,			        T_PAD,			        T_PAD,           !LONG_OP, !ENC,  SHORT, !CARRY, T_PAD}, "if the carry is set, jump to the address at the argument"},

	[op_add]	=	 {"add",		add,	10,	   3,    .meta.of = {T_REG,			        T_REG,			        T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, "add the first two arguments and put result in the 3rd"},
	[op_sub]	=	 {"sub",		sub,	10,	   3,    .meta.of = {T_REG,			        T_REG,			        T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, "ALU"},
	[op_and]	=	 {"and",		and,    6,	   3,    .meta.of = {T_REG,			        T_REG,			        T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, "ALU"},
	[op_or]		=	 {"or",			or,	    6,	   3,    .meta.of = {T_REG,			        T_REG,			        T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, "ALU"},
	[op_xor]	=	 {"xor",		xor,    6,	   3,    .meta.of = {T_REG,					T_REG,			        T_REG,           !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, "ALU"},

	[op_ld]		=	 {"ld",	        ld,		5,	   3,    .meta.of = {T_DIR | T_IND,			T_REG,					T_PAD,			 !LONG_OP,  ENC, !SHORT,  CARRY, T_PAD}, "load from argument to register, set carry if loaded zero"},
	[op_st]		=	 {"st",			st,		5,	   2,	 .meta.of = {T_REG,					T_IND | T_REG,			T_PAD,           !LONG_OP,  ENC, !SHORT, !CARRY, T_PAD}, "set memory value from the register"},
	[op_ldi]	=	 {"ldi",		ldi,    25,	   3,	 .meta.of = {T_REG | T_DIR | T_IND, T_DIR | T_REG,			T_REG,           !LONG_OP,  ENC,  SHORT, !CARRY, T_PAD}, "same as ld but can address a further range"},
	[op_sti]	=	 {"sti",		sti,	25,	   2,    .meta.of = {T_REG,					T_REG | T_DIR | T_IND,  T_DIR | T_REG,   !LONG_OP,  ENC,  SHORT, !CARRY, T_PAD}, "same concept of ldi applied on st"},
	[op_lld]	=	 {"lld",		lld,	800,   2,	 .meta.of = {T_DIR | T_IND,			T_REG,					T_PAD,			  LONG_OP,  ENC ,!SHORT,  CARRY, T_PAD}, "same as normal ld, but does not the memory restriction of IDX_MOD"},
	[op_lldi]	=	 {"lldi",		lldi,	50,	   3,	 .meta.of = {T_REG | T_DIR | T_IND, T_DIR | T_REG,	    	T_REG,			  LONG_OP,  ENC,  SHORT,  CARRY, T_PAD}, "same as lldi, but also does not have the memory restriction of IDX_MOD"},

	[op_fork]	=	 {"fork",		fork_,	10,	   1,	 .meta.of = {T_DIR,					T_PAD,			    	T_PAD,			 !LONG_OP, !ENC,  SHORT, !CARRY, T_PAD}, "creates a new process with program counter at the given argument"},
	[op_lfork]	=	 {"lfork",		lfork,	1000,  1,	 .meta.of = {T_DIR,					T_PAD,			    	T_PAD,			  LONG_OP, !ENC,  SHORT, !CARRY, T_PAD}, "same a normal fork, but it has no memory restriction on the argument"},

	[op_aff]	=	 {"aff",		aff,	2,	   1,	 .meta.of = {T_REG,					T_PAD,			        T_PAD,			 !LONG_OP,  ENC, !SHORT, !CARRY, T_PAD}, "show a character as ascii"},

	[op_nop] = { .name = "nop" },
};
