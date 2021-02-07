#include "parser.h"

t_st			read_file(int ac, const char *av[])
{
	t_st			st;
	
	if ((st = parse_arguments(ac, av)))
		return (compile(av[1]);
	else
		return (st);
}
