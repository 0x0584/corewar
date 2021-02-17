#include "parser.h"

t_hash	g_op_lookup = NULL;

static void				ops_init(void)
{
	enum e_operations		op;

	g_op_lookup = hash_alloc(op_count, blob_keep);
	op = op_nop;
	while (op < op_count)
	{
		hash_add(g_op_lookup, g_ops[op].name, g_ops + op);
		op++;
	}
}

int						main(int ac, const char *av[])
{
	t_st					st;

	ops_init();
	st = read_file(ac, av);
	hash_del(&g_op_lookup);
	return (st);
}
