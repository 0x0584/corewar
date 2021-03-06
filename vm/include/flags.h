#ifndef FLAGS_H
# define FLAGS_H

# include "vm.h"

// flags: [-dump nbr_cycles] [[-n number] champion1.cor]

typedef bool	(*t_opt_calback)(const char *arg);

typedef struct	s_flags
{
	const char		shot_opt;
	const char		*long_opt;

	t_op_callback	callback;
}				t_flags;

t_st			parse_flag(const char *arg);
t_st			parse_flags(int ac, const char *av[]);

extern t_hash	g_opts;

#endif
