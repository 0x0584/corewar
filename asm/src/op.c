/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:23:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/19 15:43:32 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "op_impl.h"

static char		op_str[MAX_OP_NAME];

static void		skip_whitespace(const char **ptr)
{
	if (ptr && *ptr)
		while (ft_isspace(**ptr))
			*ptr += 1;
}

static void		find_op(const char *key, void *blob, void *arg)
{
	if (((t_pair *)arg)->first)
		return ;
	else if (!ft_strncmp(key, op_str, MAX_OP_NAME))
	{
		ft_memcpy((void *)&((t_op *)(((t_pair *)arg)->second))->info,
				  blob, sizeof(t_op_info));
		((t_pair *)arg)->first = ((t_pair *)arg)->second;
	}
}


static inline t_u8		arg_valid_types(const t_op *op, t_arg arg)
{
	if (arg == 0)
		return op->info.meta.of.arg1_t;
	else if (arg == 1)
		return op->info.meta.of.arg2_t;
	else if (arg == 2)
		return op->info.meta.of.arg3_t;
	else
		return op->info.meta.of.padding;
}

static t_st		read_arg_type(const t_op *op, const char **arg_line, t_arg *out_type)
{
	const char *ptr;
	char reg[3];
	
	if (!*(ptr = *arg_line))
	{
		ft_dprintf(2, " end of line while expecting argument \n");		
		return st_error;
	}
	else if (*ptr == deli_reg)
	{
		if (!ft_isdigit(reg[0] = *++ptr))
		{
			ft_dprintf(2, " register is invalide \n");					
			return st_error;
		}
	}
	else if (*ptr == DIRECT_CHAR)
	{
		if (*++ptr == LABEL_CHAR)
		{
			*out_type = T_LAB;
		}
		else
		{
 			*out_type = T_DIR;			
		}
	}
	else		
	{
		if (*++ptr == LABEL_CHAR)
		{
			*out_type = T_LAB;			
		}
		else
		{
			*out_type = T_IND;						
		}		
	}
	return st_fail;
}

static t_st		fetch_arg(t_op *op, t_arg arg, const char **arg_line)
{
	t_arg			type;
	t_st			st;
	
	ft_dprintf(2, " reading argument %hhu of operation %s at `%s`\n",
			   op->info.name, arg, arg_line);
	if ((st = read_arg_type(op, arg_line, &type)))
		return st;
	else if (arg_valid_types(op, arg) | type)
	{
		op->info.args.v[arg];
		return st_succ;		
	}
	else
	{
		ft_dprintf(2, " argument %hhu accept types %04b\n", arg, arg_valid_types(op, arg));		
		return st_fail;		
	}
}

static t_st		fetch_op_args(t_op *op, const char *args_line)
{
	t_arg			arg;
	t_st			st;

	arg = 0;
	ft_dprintf(2, " fetching args for `%s`\n", args_line);
	skip_whitespace(&args_line);
	while (arg < op->info.nargs)
		if ((st = fetch_arg(op, arg++, &args_line)))
			return (st);
	
	if (*args_line)
	{
		ft_dprintf(2, " operetaion arguments exceeded : `%s`\n", args_line);
		return st_fail;
	}
	else
		return st_succ;
}

t_st			parse_op(t_op *op, const char *buff)
{
	const char		*spc;
	t_pair			op_fetcher;

	skip_whitespace(&buff);
	if (!*buff)
	{
		ft_dprintf(2, " >> empty line\n");
		return st_fail;
	}
	else if (!(spc = ft_strchr(buff, ' ')))
	{
		ft_dprintf(2, "no arguments are found\n");
		return st_error;
	}

	ft_bzero(op_str, 5);
	ft_strncpy(op_str, buff, min(spc - buff - 1, 4));
	op_fetcher = (t_pair){NULL, op};
	hash_iter_arg(g_op_lookup, &op_fetcher, find_op);
	if (op_fetcher.first)
		return (fetch_op_args(op, spc));
	else
	{
		ft_dprintf(2, "unknow operation `%s`\n", op_str);
		return (st_error);
	}
}

t_st			write_op(t_op *op, t_u8 *buff, t_u16 size)
{

}

t_st			write_prog(t_lst ops, const char *out)
{

}
