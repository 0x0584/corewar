#include "parser.h"
#include "op_impl.h"


t_u8			arg_offset(const t_op_info *info, t_arg arg)
{
	t_arg			type;

	if ((type = encoded(op_encoding(info, arg++))) == T_REG)
		return 1;
	else if (type == T_DIR)
		return info->meta.of.short_chunk ? IND_SIZE : REG_SIZE;
	else
		return IND_SIZE;

}

static t_u8		op_memory_footprint(const t_op *op)
{
	t_u8			size;
	t_arg			arg;

	size = 1;
	if (op->info.meta.of.encoded)
		size += 1;
	arg = 0;
	while (arg < op->info.nargs)
		size += arg_offset(&op->info, arg++);
	return (size);
}

t_s16		write_arg(const t_op_info *info, const t_arg arg, t_s16 at)
{
	t_arg			type;

	if ((type = encoded(op_encoding(info, arg))) == T_REG)
		g_champ.file[at++] = info->args.v[arg];
	else if (type == T_DIR && !info->meta.of.short_chunk)
	{
		g_champ.file[at++] = info->args.c[arg].val.byte_1;
		g_champ.file[at++] = info->args.c[arg].val.byte_2;
		g_champ.file[at++] = info->args.c[arg].val.byte_3;
		g_champ.file[at++] = info->args.c[arg].val.byte_4;
	}
	else
	{
		g_champ.file[at++] = info->args.c[arg].val.byte_1;
		g_champ.file[at++] = info->args.c[arg].val.byte_2;
	}
	return (at);
}

static void		write_args(const t_op *op, t_s16 *size)
{
	t_arg			arg;

	arg = 0;
	while (arg < op->info.nargs)
		*size += write_arg(&op->info, arg++, *size);
}

void			write_op(void *blob, void *size)
{
	t_op			*op;
	t_s16			at;

	if (!(op = blob) || (at = *(t_s16 *)size) < 0)
		return ;
	else if ((at + op_memory_footprint(op)) < CHAMP_MAX_SIZE)
	{
		op->addr = *(t_s16 *)size;
		g_champ.file[at++] = op->info.code;
		if (op->info.meta.of.encoded)
			g_champ.file[at++] = op->info.encoded.encod;
		write_args(op, &at);
		*(t_s16 *)size = at;
	}
	else
		*(t_s16 *)size = -1;
}
