#include "parser.h"
#include "op_impl.h"

static t_st		parse_arg_label(t_op *op, t_arg arg, const char **arg_line)
{
	const char *walk;
	char		*label;

	if (**arg_line != LABEL_CHAR)
		return (st_fail);

	*arg_line += 1;
	walk = *arg_line;
	while (*walk && !ft_isspace(*walk) && *walk != deli_comma)
		walk++;

	if (!*walk)
	{
		ft_dprintf(2, " %{yellow_fg}end of line%{reset}\n");
		return st_succ;
	}
	else if (!(ft_isspace(*walk) || *walk == deli_comma))
	{
		ft_dprintf(2, " %{red_fg}invalid separator%{reset}\n");
		return st_error;
	}
	else
	{
		label = ft_strrdup(*arg_line, walk - 1);

		walk = label;
		while (*walk)
		{
			if (!ft_strchr(LABEL_CHARS, *walk))
			{
				ft_dprintf(2, "%{red_fg}label contains illigale characters%{reset}\n");
				return st_error;
			}
			walk++;
		}

		*arg_line = ++walk;
		skip_whitespace(arg_line);
		op->labels[arg] = label;
		return (st_succ);
	}
}

static t_st		parse_arg_value_base(t_op *op, t_arg arg, const char **arg_line)
{
	return (st_error);
}

t_st			parse_arg_value(t_op *op, t_arg arg, const char **arg_line)
{
	if (parse_arg_label(op, arg, arg_line))
		return (parse_arg_value_base(op, arg, arg_line));
	else
		return (st_succ);
}
