#include "vm.h"
#include "process.h"

t_u8	nop(t_proc proc)
{
	return 0;
}

t_u8	live(t_proc proc)
{
	g_vm.winner = proc->op.args.v[0];
	proc->alive = true;
	g_vm.lives++;
}

t_u8	zjmp(t_proc proc)
{

}

t_u8	aff(t_proc proc)
{

}
