/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:30:44 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 17:45:28 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "args.h"
#include "op_impl.h"

static char		*filename(const char *in)
{
	char			*out;
	char			*ext;
	if (!(ext = ft_strrchr(in, '.')))
		return (NULL);
	else
	{
		out = ft_strrdup(in, ext - 1);
		ft_strappend(&out, ".cor");
		return (out);
	}
}

t_st			read_file(const int ac, const char *av[])
{
	t_lst			file;
	int				fd;
	char			*buff;
	char			*outname;
	t_st			st;

	if (ac < 2)
	{
		ft_dprintf(2, "no file was provided to %s.", av[0]);
		return (st_error);
	}
	else if (!(outname = filename(av[1])))
		return (st_error);
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_dprintf(2, "cannot open file", av[1]);
		return (st_fail);
	}
	else
	{
		file = lst_alloc(blob_free);
		while (gnl(fd, &buff))
			if (!*buff || parse_line(&buff))
				free(buff);
			else
				lst_push_back_blob(file, buff, sizeof(char *), false);
		gnl_clean(fd);
		st = compile(file, outname);
		lst_del(&file);
		free(outname);
		close(fd);
		return st;
	}
}

 t_st				read_reg(t_op *op, const t_arg arg, const char **arg_line)
{
	char			reg[3];
	t_u8			reg_num;

	/* if (!ft_isdigit(reg[0] = *++ptr)) */
	/* { */
	/* 	ft_dprintf(2, " register is invalide \n"); */
	/* 	return st_error; */
	/* } */

	ft_bzero(reg, 3);
	if (ascii_to_digit(arg_line, reg))
	{
		if (ascii_to_digit(arg_line, reg + 1))
		{
			if (!(reg_num = ft_atoi(reg)) || reg_num > REG_NUMBER)
			{
				ft_dprintf(2, " %{yellow_fg}argument %hhu of operation `%s`"
						   " has invalid register access%{reset}\n",
						   op->info.name, arg);
				return st_fail;
			}
			else
			{
				op->info.args.v[0] = reg_num;
				return st_succ;
			}
		}
		else
		{
			ft_dprintf(2, " %{red_fg}register is invalide%{reset} \n");
			return st_error;
		}
	}
	else
	{
		ft_dprintf(2, " register is invalide \n");
		return st_error;
	}
}

 t_st				read_dir(t_op *op, const t_arg arg, const char **arg_line)
{

}

 t_st				read_ind(t_op *op, const t_arg arg, const char **arg_line)
{

}



static void			set_type(const char **arg_line, t_arg *type, t_u8 type_)
{
	*type = type_;
	if (*(*arg_line + 1) == LABEL_CHAR)
		*type |= T_LAB;
}

t_st				read_arg(t_op *op, const t_arg arg, const char **arg_line)
{
	t_arg				type;

	if (**arg_line == deli_reg)
		return read_reg(op, arg, arg_line);
	else if (**arg_line == DIRECT_CHAR)
		set_type(arg_line, &type, T_DIR);
	else if (ft_isdigit(**arg_line))
		set_type(arg_line, &type, T_IND);
	else
	{
		ft_dprintf(2, "%{cyan_fg}%s: arg %d: %{red_fg}unknown argument type%{reset}",
				   op->info.name, arg);
		return (st_error);
	}

	if (type | arg_valid_types(op, arg))
	{
		op->info.args.v[arg] = ;
		return (parse_arg_value(op, arg, arg_line));
	}
	else
	{
		ft_dprintf(2, " %{yellow_fg}argument %hhu accept types %04b%{reset}\n",
				   arg, arg_valid_types(op, arg));
		return (st_fail);
	}

	return (st_fail);
}
