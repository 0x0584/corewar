/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:02:40 by archid-           #+#    #+#             */
/*   Updated: 2021/02/18 18:10:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_impl.h"
#include "op_callback.h"
#include "process.h"

void				op_dump(const t_op *op, bool dump_args, bool dump_verbose)
{
	t_arg arg;

	ft_dprintf(g_fd, " ### op `%s`:\n %u", op->info.name, op->info.nargs);
	ft_dprintf(g_fd, "   encoding : %02x %08b ", op->info.encoded.encod, op->info.encoded.encod);
	ft_dprintf(g_fd, "   expecting arg1: %04b, arg2: %04b, arg3: %04b\n",
			   op->info.meta.of.arg1_t, op->info.meta.of.arg2_t, op->info.meta.of.arg3_t);
	if (dump_verbose)
	{
		ft_dprintf(g_fd, "   %s %s sizeof %s %s\n\n",
				   op->info.meta.of.long_op ? "long" : "idx_mod",
				   op->info.meta.of.encoded ? "encoded" : "not encoded",
				   op->info.meta.of.short_chunk ? "short" : "int",
				   op->info.meta.of.carry ? "has carry" : "");
	}
	if (dump_args)
	{
		arg = 0;
		while (arg < op->info.nargs)
		{
			ft_dprintf(g_fd, "    arg %u: short(%hd) int(%d) %08x: %02x%02x %02x%02x\n", arg,
					   op->info.args.c[arg].short_chunk,
					   op->info.args.c[arg].chunk,
					   op->info.args.c[arg].chunk,

					   op->info.args.c[arg].val.byte_4, op->info.args.c[arg].val.byte_3,
					   op->info.args.c[arg].val.byte_2, op->info.args.c[arg].val.byte_1
				);
			arg++;
		}
	}
	ft_dprintf(g_fd, " ###\n");
}

t_op		g_op[op_count] = {
 	[op_live]	=	 {.callback = live,		10},

 	[op_zjmp]	=	 {.callback = zjmp,		20},

 	[op_add]	=	 {.callback = add,		10},
 	[op_sub]	=	 {.callback = sub,		10},
 	[op_and]	=	 {.callback = and,		6},
 	[op_or]		=	 {.callback = or,		6},
 	[op_xor]	=	 {.callback = xor,		6},

 	[op_ld]		=	 {.callback = ld,		5},
 	[op_st]		=	 {.callback = st,		5},
 	[op_ldi]	=	 {.callback = ldi,		25},
 	[op_sti]	=	 {.callback = sti,		25},

 	[op_lld]	=	 {.callback = lld,		10},
 	[op_lldi]	=	 {.callback = lldi,		50},

 	[op_fork]	=	 {.callback = fork_,	800},
	[op_lfork]	=	 {.callback = lfork,	1000},

	[op_aff]	=	 {.callback = aff,		2},

	[op_nop]	=	 {.callback = nop,		0},
};


void set_ops(void)
{
	t_op_code	code;

	code = op_nop;
	while (code < op_count)
	{
		ft_memcpy(&g_op[code].info, g_ops + code, sizeof(t_op_info));
		code++;
	}
}
