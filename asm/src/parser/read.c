#include "reader.h"
#include "args.h"

static inline t_u8	fetch_type(t_op_info *info, t_arg arg, t_u8 type, char prefix)
{
	if (prefix == LABEL_CHAR)
	{
		if (arg == 0)
			info->meta.of.arg1_t |= T_LAB;
		else if (arg == 1)
			info->meta.of.arg2_t |= T_LAB;
		else if (arg == 2)
			info->meta.of.arg3_t |= T_LAB;
		else
			assert(arg < MAX_ARGS_NUMBER);
	}
	return uncode(type);
}

static inline void	set_encoding(t_op *op, t_arg arg, t_u8 type, char prefix)
{
	if (arg == 0)
		op->info.encoded.args.arg_1 = fetch_type(&op->info, arg, type, prefix);
	else if (arg == 1)
		op->info.encoded.args.arg_2 = fetch_type(&op->info, arg, type, prefix);
	else if (arg == 2)
		op->info.encoded.args.arg_3 = fetch_type(&op->info, arg, type, prefix);
	else
	    op->info.encoded.args.padding = T_PAD;
}

t_st				read_arg(t_op *op, const t_arg arg, const char **arg_line)
{
	skip_whitespace(arg_line);
	if (**arg_line == deli_reg)
		return read_reg(op, arg, arg_line);
	else if (**arg_line == DIRECT_CHAR)
	{
		*arg_line += 1;
		set_encoding(op, arg, T_DIR, **arg_line);
	}
	else if (ft_isdigit(**arg_line) || **arg_line == LABEL_CHAR)
		set_encoding(op, arg, T_IND, **arg_line);
	else
	{
		ft_dprintf(2, "%{cyan_fg}%s: arg %d: %{red_fg}unknown argument type%{reset}",
				   op->info.name, arg);
		return (st_error);
	}
	if (op_encoding(&op->info, arg) | arg_valid_types(op, arg))
		return (parse_arg_value(op, arg, arg_line));
	else
	{
		ft_dprintf(2, " %{red_fg}argument %hhu accept types %04b%{reset}\n",
				   arg, arg_valid_types(op, arg));
		return (st_error);
	}
}
