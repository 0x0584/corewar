#include "memory.h"
#include "process.h"

/**
 * \brief write operation arg into arena at pc relative to offset
 *
 * st/sti are the only operation to set memory both set the value of REG_SIZE
 */
void				mem_write_chunk(const t_proc p, t_arg arg, t_u8 offset)
{
	print_arena();
	g_vm.arena[pc_shift(p->pc, offset, p->op.meta.of.long_op)] = p->op.args.c[arg].val.byte_1;
	g_vm.arena[pc_shift(p->pc, offset + 1, p->op.meta.of.long_op)] = p->op.args.c[arg].val.byte_2;
	g_vm.arena[pc_shift(p->pc, offset + 2, p->op.meta.of.long_op)] = p->op.args.c[arg].val.byte_3;
	g_vm.arena[pc_shift(p->pc, offset + 3, p->op.meta.of.long_op)] = p->op.args.c[arg].val.byte_4;
	print_arena();
}
