#include "vm.h"
#include "process.h"
#include "memory.h"

void		set_nop(t_proc p)
{
	ft_memcpy(&p->op, &g_ops[op_nop], sizeof(t_op));
}

void		nop(t_proc proc)
{
	(void)proc;
}

void		live(t_proc proc)
{
	t_dir id;

	g_vm.lives++;
	proc->lives++;
	if ((id = -arg_value(proc, 0, false)) && id <= g_vm.nplayers)
		g_vm.winner = id;
}

void		zjmp(t_proc proc)
{
	if (proc->carry)
		proc->pc = shift_pc(proc, arg_value(proc, 0, false));
}

void		aff(t_proc proc)
{
	ft_printf("AFF: %c\n", arg_value(proc, 0, false));
}
