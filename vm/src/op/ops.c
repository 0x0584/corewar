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

static t_u8 update_live(t_s32 id)
{
	return id;
}

void	live(t_proc proc)
{
	g_vm.lives++;
	g_vm.winner = update_live(proc->op.args.v[0]);
}

void	zjmp(t_proc proc)
{
	if (proc->carry)
		proc->pc = shift_pc(proc, arg_value(proc, 0, false));
}

void	aff(t_proc proc)
{
	ft_printf("AFF: %c\n", arg_value(proc, 0, false));
}
