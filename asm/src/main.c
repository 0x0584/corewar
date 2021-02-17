# include "parser.h"

t_hash	g_ops = NULL;

static void ops_hash_init(void)
{
	enum e_operations op;

	g_ops = hash_alloc(op_count, blob_free);
	op = op_nop;
	while (op < op_count)
	{
		hash_add();
	}
}

int		main(int ac, const char *av[])
{
	t_st st;

	ops_hash_init();
	st = read_file(ac, av);
	hash_del(&g_ops);
	return (st);
}
