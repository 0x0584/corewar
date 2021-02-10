#include "memory.h"
#include "process.h"

void				mem_read_chunk(const t_proc p, t_arg arg, t_u8 *offset)
{
	p->op.args.c[arg].val.byte_1 = at_mem(pc_shift(p->pc, *offset, p->op.meta.of.long_op));
	p->op.args.c[arg].val.byte_2 = at_mem(pc_shift(p->pc, *offset + 1, p->op.meta.of.long_op));
	*offset += 2;
	if (!p->op.meta.of.short_chunk && encoded(op_encoding(p, arg)) == T_DIR)
	{
		p->op.args.c[arg].val.byte_3 = at_mem(pc_shift(p->pc, *offset, p->op.meta.of.long_op));
		p->op.args.c[arg].val.byte_4 = at_mem(pc_shift(p->pc, *offset + 1, p->op.meta.of.long_op));
		*offset += 2;
	}
}
