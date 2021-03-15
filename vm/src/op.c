/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:10:57 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 22:59:43 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

#define OP_BUFF 128

static char	g_op_buff[OP_BUFF + 1];

static int	short_chunk_disam(const t_op_info *info, t_arg arg, int offset)
{
	return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %hd",
						info->args.c[arg].short_chunk));
}

static int	chunk_disam(const t_op_info *info, t_arg arg, int offset)
{
	return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %d",
						info->args.c[arg].chunk));
}

static int	reg_disasm(const t_proc p, t_arg arg, int offset)
{
	if (op_meta_encoding(&p->op.info, arg) == T_REG)
		return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset,
					" r%d", p->op.info.args.v[arg]));
	else
		return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %d",
					p->reg[p->op.info.args.v[arg]]));
}

static int	op_disasm_arg(const t_proc p, t_arg arg, int offset)
{
	t_arg			type;

	if (p->op.info.meta.of.encoded)
	{
		if ((type = decode(op_encoding(&p->op.info, arg))) == T_REG)
			return (reg_disasm(p, arg, offset));
		else if (type == T_DIR && !p->op.info.meta.of.short_chunk)
			return (chunk_disam(&p->op.info, arg, offset));
		else
			return (short_chunk_disam(&p->op.info, arg, offset));
	}
	else if (p->op.info.meta.of.short_chunk)
		return (short_chunk_disam(&p->op.info, arg, offset));
	else
		return (chunk_disam(&p->op.info, arg, offset));
}

const char	*op_disasm(const t_proc p)
{
	int				off;
	t_arg			arg;

	off = ft_snprintf(g_op_buff, OP_BUFF, "%s", p->op.info.name);
	arg = 0;
	while (arg < p->op.info.nargs)
		off += op_disasm_arg(p, arg++, off);
	if (p->op.info.code == op_fork)
		off += ft_snprintf(g_op_buff + off, OP_BUFF - off, " (%hd)",
						p->op.info.args.c[0].short_chunk % IDX_MOD + p->pc);
	else if (p->op.info.code == op_lfork)
		off += ft_snprintf(g_op_buff + off, OP_BUFF - off, " (%hd)",
						p->op.info.args.c[0].short_chunk + p->pc);
	ft_snprintf(g_op_buff + off, OP_BUFF - off, "\n");
	return (g_op_buff);
}

static int	short_chunk_bytecode(const t_op_info *info, t_arg arg, int offset)
{
	return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %02x %02x",
							info->args.c[arg].val.byte_2,
							info->args.c[arg].val.byte_1));
}

static int	chunk_bytecode(const t_op_info *info, t_arg arg, int offset)
{
	return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset,
						" %02x %02x %02x %02x",
						info->args.c[arg].val.byte_4,
						info->args.c[arg].val.byte_3,
						info->args.c[arg].val.byte_2,
						info->args.c[arg].val.byte_1));
}

static int	op_bytecode_arg(const t_op_info *info, t_arg arg, int offset)
{
	t_arg			type;

	if (info->meta.of.encoded)
	{
		if ((type = decode(op_encoding(info, arg))) == T_REG)
			return (ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %02x",
								info->args.v[arg]));
		else if (type == T_DIR && !info->meta.of.short_chunk)
			return (chunk_bytecode(info, arg, offset));
		else
			return (short_chunk_bytecode(info, arg, offset));
	}
	else if (info->meta.of.short_chunk)
		return (short_chunk_bytecode(info, arg, offset));
	else
		return (chunk_bytecode(info, arg, offset));
}

const char	*op_bytecode(const t_op_info *info)
{
	int				off;
	t_arg			arg;

	off = ft_snprintf(g_op_buff, OP_BUFF, "%02x", info->code);
	if (info->meta.of.encoded)
		off += ft_snprintf(g_op_buff + off, OP_BUFF - off, " %02x",
							info->encoded.encod);
	arg = 0;
	while (arg < info->nargs)
		off += op_bytecode_arg(info, arg++, off);
	ft_snprintf(g_op_buff + off, OP_BUFF - off, " \n");
	return (g_op_buff);
}
