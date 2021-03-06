#include "vm.h"
#include "process.h"
#include "memory.h"

void		set_nop(t_proc p)
{
	ft_memcpy(&p->op, &g_op[op_nop], sizeof(t_op));
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
	{
		g_vm.winner = id;
		ft_dprintf(g_fd, "process %d said player (%d) is alive\n", proc->pid, id);
	}
	else
	{
		ft_dprintf(g_fd, "process %d declared (%d) as alive\n", proc->pid, id);
	}
}

void		zjmp(t_proc proc)
{
	t_ind addr;

	addr = arg_value(proc, 0, false);
	ft_dprintf(g_fd, "zjmp %hd ", addr);
	if (proc->carry)
		proc->pc = shift_pc(proc, addr);
	ft_putendl_fd(proc->carry ? "OK" : "FAIL", g_fd);
}

void		aff(t_proc proc)
{
	t_dir		c;

	if (ft_isprint(c = arg_value(proc, 0, false)))
		ft_printf("AFF: %c\n", c);
	else
		ft_printf("AFF: %x\n", c);
}
