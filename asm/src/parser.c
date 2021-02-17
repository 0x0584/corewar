/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:22:26 by archid-           #+#    #+#             */
/*   Updated: 2021/02/17 17:50:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_champ	g_champ;
static int		g_header_status = 0;
static t_u8		g_name[PROG_NAME_LENGTH + 1];
static char		g_comment_prefix[] = {
	COMMENT_CHAR, ';', '\0'
};

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

static t_st		match_cmd(t_u8 *buff, size_t length, const char *cmd, const char *line)
{
	size_t			len;
	size_t			i;

	len = ft_strlen(cmd);
	if (ft_strncmp(line, cmd, len))
		return (st_fail);
	line += len;
	if (!ft_isspace(*line++))
	{
		ft_dprintf(2, "no space after command\n");
		return (st_error);
	}
	while (ft_isspace(*line))
		line++;
	if (!*line)
	{
		ft_dprintf(2, "end of line before command arg\n");
		return (st_error);
	}
	else if (*line++ == '\"')
	{
		i = 0;
		while (i < length && line[i] && line[i] != '\"')
		{
			buff[i] = line[i];
			i++;
		}
		if (i == length)
		{
			ft_dprintf(2, "exceeding the maximum length %d of %s\n", length, cmd);
			return (st_error);
		}
		else if (!line[i])
		{
			ft_dprintf(2, "no delimiter, expecting \"\n");
			return (st_error);
		}
		else
		{
			g_header_status++;
			return (st_succ);
		}
	}
	else
	{
		ft_dprintf(2, "wrong delimiter, expecting \"\n");
		return (st_error);
	}
}

static t_st		match_name(const char *line)
{
	t_st			st;

	if ((st = match_cmd(g_name, PROG_NAME_LENGTH, NAME_CMD_STRING, line)))
		return (st);
	else if (st == st_succ)
	{
		if (g_header_status != 1)
		{
			ft_dprintf(2, "name command appeared twice\n");
			return (st_error);
		}
		else
			return (st_succ);
	}
	else
		return (st_fail);
}

static t_st		match_comment(const char *line)
{
	t_st			st;

	if ((st = match_cmd(g_champ.comment, COMMENT_LENGTH, COMMENT_CMD_STRING, line)))
		return (st);
	else if (st == st_succ)
	{
		if (g_header_status != 2)
		{
			ft_dprintf(2, "comment command appeared twice\n");
			return (st_error);
		}
		else
			return (st_succ);
	}
	else
		return (st_fail);
}

static t_st		parse_header(const char *line)
{
	const char		*walk;
	t_st			st;

	walk = line;
	st = st_fail;
	while (*walk && ft_isspace(*walk))
		walk++;
	if (!*walk)
		return (st_fail);
	else if ((st = match_name(line)) == st_fail)
	{
		if ((st = match_comment(line)))
			return (st);
		else
			return (st_succ);
	}
	else if (st == st_succ)
		return (st);
	else
		return (g_header_status == 2 ? st_succ : st_error);
}

t_st			parse_line(char **line)
{
	const char		*instr;
	t_st			st;

	if (!line || !*line)
		return (st_error);
	else if ((st = parse_header(*line)) == st_error)
		return (st_error);
	else if (st == st_succ)
		return (st_fail);
	else
	{
		if (ft_strchr(g_comment_prefix, *line[0]))
			return (st_fail);
		else
		{
			instr = *line;
			while (*instr)
			{
				if (ft_strchr(g_comment_prefix, *instr))
				{
					ft_strchange(line, ft_strrdup(*line, instr));
					break;
				}
				else
					instr++;
			}
			return (st_succ);
		}
	}
}

static void		dump_line(void *str)
{
	ft_printf("`%s`\n", str);
}

static t_st		compile(t_lst file, const char *outname)
{
	t_lst			ops;
	t_st			st;

	if ((ops = parse_ops(file)))
	{
		st = write_bin(ops, outname);
		lst_del(&ops);
		return st;
	}
	else
		return st_error;
}

t_st			parse_op(t_blob *args, const char *buff)
{

	return st_error;
}

t_lst			parse_ops(t_lst lines)
{
	t_lst			ops;
	t_lstnode		walk;
	t_blob			blob;

	ops = lst_alloc(blob_free);
	walk = lst_front(lines);
	while (walk)
	{
		if (parse_op(&blob, walk->blob))
		{
			lst_del(&ops);
			break;
		}
		lst_node_forward(&walk);
	}
	return ops;
}

t_st			write_bin(t_lst ops, const char *out)
{
	return st_succ;
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
