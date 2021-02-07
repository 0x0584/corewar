#include "flags.h"

t_st			parse_arguments(int ac, char *av[])
{
	if (ac == 1)
		return (error_raise(err_no_file, print_usage, av[0]));
	else if (ac > 3)
		return (error_raise(err_no_file, print_usage, av[0]));
}

struct s_flags	g_flags;
