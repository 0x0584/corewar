#include "op_impl.h"

bool		op_meta_short(const t_op *op)
{
	return op && op->info.meta.of.short_chunk;
}

bool		op_meta_long(const t_op *op)
{
	return op && op->info.meta.of.long_op;
}
