#include "vm.h"
#include "process.h"
#include "memory.h"

void		set_nop(t_proc p)
{
	ft_memcpy(&p->op, &g_ops[op_nop], sizeof(t_op));
}

void	nop(t_proc proc)
{
	(void)proc;
}

void	live(t_proc proc)
{
	g_vm.winner = proc->op.args.v[0];
	proc->alive = true;
	g_vm.lives++;
}

void	zjmp(t_proc proc)
{
	if (proc->carry)
		proc->pc = shift_pc(proc, arg_value(proc, 0, false));
}

void	aff(t_proc proc)
{
	ft_printf("AFF: %c\n", proc->op.args.c[0].val.byte_1);
}
