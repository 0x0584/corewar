#include "op.h"

#define OP_BUFF 128

static char		g_op_buff[OP_BUFF + 1];

static int		short_chunk_disam(const t_op_info *info, t_arg arg, int offset)
{
	return ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %hd",
					   info->args.c[arg].short_chunk);
}

static int		chunk_disam(const t_op_info *info, t_arg arg, int offset)
{
	return ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %d",
					   info->args.c[arg].chunk);
}

static int		op_disasm_arg(const t_op_info *info, t_arg arg, int offset)
{
	t_arg			type;

	if (info->meta.of.encoded)
	{
		if ((type = decode(op_encoding(info, arg))) == T_REG)
			return ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " r%d",
							   info->args.v[arg]);
		else if (type == T_DIR && !info->meta.of.short_chunk)
			return chunk_disam(info, arg, offset);
		else
			return short_chunk_disam(info, arg, offset);
	}
	else if (info->meta.of.short_chunk)
		return short_chunk_disam(info, arg, offset);
	else
		return chunk_disam(info, arg, offset);
}

const char		*op_disasm(const t_op_info *info)
{
	int				off;
	t_arg			arg;

	off = ft_snprintf(g_op_buff, OP_BUFF, "%s", info->name);
	arg = 0;
	while (arg < info->nargs)
		off += op_disasm_arg(info, arg++, off);
	ft_snprintf(g_op_buff + off, OP_BUFF - off, "\n");
	return g_op_buff;
}

static int		short_chunk_bytecode(const t_op_info *info, t_arg arg, int offset)
{
	return ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %02x %02x",
					   info->args.c[arg].val.byte_2,
					   info->args.c[arg].val.byte_1);
}

static int		chunk_bytecode(const t_op_info *info, t_arg arg, int offset)
{
	return ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %02x %02x %02x %02x",
					   info->args.c[arg].val.byte_4,
					   info->args.c[arg].val.byte_3,
					   info->args.c[arg].val.byte_2,
					   info->args.c[arg].val.byte_1);
}

static int		op_bytecode_arg(const t_op_info *info, t_arg arg, int offset)
{
	t_arg			type;

	if (info->meta.of.encoded)
	{
		if ((type = decode(op_encoding(info, arg))) == T_REG)
			return ft_snprintf(g_op_buff + offset, OP_BUFF - offset, " %02x",
							   info->args.v[arg]);
		else if (type == T_DIR && !info->meta.of.short_chunk)
			return chunk_bytecode(info, arg, offset);
		else
			return short_chunk_bytecode(info, arg, offset);
	}
	else if (info->meta.of.short_chunk)
		return short_chunk_bytecode(info, arg, offset);
	else
		return chunk_bytecode(info, arg, offset);
}

const char		*op_bytecode(const t_op_info *info)
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
	return g_op_buff;
}
