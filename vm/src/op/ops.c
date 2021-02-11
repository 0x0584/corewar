#include "vm.h"
#include "process.h"

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
	(void)proc;
}

void	aff(t_proc proc)
{
	(void)proc;
}
