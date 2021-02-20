/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:30:44 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 18:08:36 by archid-          ###   ########.fr       */
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

static inline t_u8	fetch_type(t_u8 type, const char **arg_line)
{
	return type | (*(*arg_line + 1) == LABEL_CHAR ? T_LAB : 0);
}

static inline void	set_type(t_op *op, t_arg arg, t_u8 type, const char **arg_line)
{
	if (arg == 0)
		op->info.encoded.args.arg_1 = fetch_type(type, arg_line);
	else if (arg == 1)
		op->info.encoded.args.arg_2 = fetch_type(type, arg_line);
	else if (arg == 2)
		op->info.encoded.args.arg_3 = fetch_type(type, arg_line);
	else
		assert(arg < MAX_ARGS_NUMBER);
}

t_st				read_arg(t_op *op, const t_arg arg, const char **arg_line)
{
	t_arg				type;

	if (**arg_line == deli_reg)
		return read_reg(op, arg, arg_line);
	else if (**arg_line == DIRECT_CHAR)
		set_type(op, arg, T_DIR, arg_line);
	else if (ft_isdigit(**arg_line))
		set_type(op, arg, T_IND, arg_line);
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
		ft_dprintf(2, " %{yellow_fg}argument %hhu accept types %04b%{reset}\n",
				   arg, arg_valid_types(op, arg));
		return (st_fail);
	}
}
