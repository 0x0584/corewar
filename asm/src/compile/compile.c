/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:25:02 by archid-           #+#    #+#             */
/*   Updated: 2021/02/26 12:17:55 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "compile.h"
#include "op_impl.h"

static int i = 0;

static void		dump_line(void *blob)
{
	ft_printf(" line %d `%s`\n", i++, blob);
}

void			dump_file(void)
{
	int i = 0;
	ft_putendl("");
	while (i < CHAMP_MAX_SIZE)
	{
		ft_printf("%02x%s", g_champ.file[i], (i+1)%2 == 0 ? " " : "");
		i++;
		if (i%32 == 0)
			ft_putendl("");
	}
	ft_putendl("");
}

static t_st		write_champion(const int fd, const char *outname)
{
	int magic = beword(COREWAR_EXEC_MAGIC);
	int prog_size = beword(g_champ.prog_size);
	int null = 0;

	if (write(fd, &magic, sizeof(int)) < (ssize_t)sizeof(int) ||
		write(fd, g_name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH ||
		write(fd, &null, sizeof(int)) < (ssize_t)sizeof(int) ||
		write(fd, &prog_size, sizeof(int)) < (ssize_t)sizeof(int) ||
		write(fd, g_champ.comment, COMMENT_LENGTH) < COMMENT_LENGTH ||
		write(fd, &null, sizeof(int)) < (ssize_t)sizeof(int) ||
		write(fd, g_champ.file, g_champ.prog_size) < g_champ.prog_size)
	{
		ft_dprintf(2, "cannot write %s\n", outname);
		return st_error;
	}
	else
	{
		ft_dprintf(2, "wrote %s\n", outname);
		return st_succ;
	}
}

t_st			compile(t_lst lines, const char *outname)
{
	t_lst			ops;
	t_st			st;
	int				fd;

	if (g_debug)
		lst_iter(lines, true, dump_line);
	if ((fd = open(outname, O_CREAT | O_TRUNC | O_WRONLY, 0777)) < 0)
	{
		ft_dprintf(2, "cannot open file descriptor for writing %s!\n", outname);
		return (st_error);
	}
	else if ((ops = parse_ops(lines)))
	{
		if ((st = write_prog(ops)) == st_succ)
			st = write_champion(fd, outname);
		lst_del(&ops);
	}
	else
	{
		ft_dprintf(2, "couldn't parse operations\n");
		st = st_error;
	}
	close(fd);
	return st;
}

static void		substitute_label(void *blob, void *st)
{
	t_op			*op;
	t_op			*label;
	t_arg			arg;
	t_s16			offset;

	if (*(t_st *)st != st_succ)
		return ;
	arg = 0;
	op = blob;
	offset = op->addr + (op->info.meta.of.encoded != 0) + 1;
	while (arg < op->info.nargs)
	{
		if (op->labels[arg])
		{
			if ((label = hash_get(g_labels, op->labels[arg], NULL)))
			{
				if (label->addr)
					op->info.args.c[arg].short_chunk =  label->addr - op->addr;
				else
				    op->info.args.c[arg].short_chunk = g_champ.prog_size;
				if (g_debug)
				{
					ft_dprintf(2, "label at %hd | op at %hd\n", label->addr , op->addr);
					ft_dprintf(2, "writing %s %04x (%hd) at %hd\n\n",
							   op->labels[arg],
							   op->info.args.c[arg].short_chunk,
							   op->info.args.c[arg].short_chunk,
							   offset);
				}
				write_arg(&op->info, arg, offset);
			}
			else
			{
				ft_dprintf(2, "referencing unknown label %s\n", op->labels[arg]);
				*(t_st *)st = st_error;
				break;
			}
		}
		offset += arg_offset(&op->info, arg++);
	}
}

static void		label_dump(const char *key, void *blob)
{
	t_op *op = blob;

	ft_dprintf(2, "%s -> [%s:%hu]\n", key, op->info.name, op->addr);
}

t_st			write_prog(t_lst ops)
{
	t_s16			size;
	t_st			st;

	size = 0;
	lst_iter_arg(ops, true, &size, write_op);
	if (size == -1)
	{
		ft_dprintf(2, "The generated byte-code exceeds the program size limit %d\n",
				   CHAMP_MAX_SIZE);
		return st_error;
	}
	if (g_debug)
	{
		dump_file();
		ft_putendl("");
		hash_iter(g_labels, label_dump);
	}
	g_champ.prog_size = size;
	st = st_succ;
	lst_iter_arg(ops, true, &st, substitute_label);
	if (g_debug)
		dump_file();
	return (st);
}

bool		g_debug = false;
