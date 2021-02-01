#include "vm.h"
#include "process.h"

void	nop(t_proc proc)
{
	(void)proc;
}

void	live(t_proc proc)
{
	/* g_vm.winner = proc->op.args[0]; */
	/* g_vm.lives++; */
}

void	zjmp(t_proc proc)
{
	/* if (proc->carry) */
	/* 	proc->pc += (proc->op.args[0] % IDX_MOD); */
}

void	aff(t_proc proc)
{

}
