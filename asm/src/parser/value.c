#include "parser.h"
#include "op_impl.h"

t_st		parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	t_arg		encod;

	encod = op_encoding(&op->info, arg);

	op->info.args.v[arg] ;

	return (st_succ);
}
