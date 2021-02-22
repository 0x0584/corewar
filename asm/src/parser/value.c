#include "parser.h"
#include "op_impl.h"

static t_st		parse_arg_label(const char *arg_line)
{
	if (*arg_line != LABEL_CHAR)
		return (st_fail);
	else
	{

		return (st_succ);
	}
}

static t_st		parse_arg_value_base()
{
	return (st_error);
}

t_st			parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	const char *walk;

	if (parse_arg_label(walk = *arg_line + (**arg_line == DIRECT_CHAR)))
		return (parse_arg_value_base(walk));
	else
		return (st_succ);
}
