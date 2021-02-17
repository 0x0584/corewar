#include "parser.h"

static t_champ	g_champ;
static bool		header_read = false;

static char		g_comment_prefix[] = {
	COMMENT_CHAR, ';', '\0'
};

static char		*filename(const char *in)
{
	char		*out;
	char		*ext;

	if (!(ext = ft_strrchr(in, '.')))
		return (NULL);
	else
	{
		out = ft_strrdup(in, ext);
		ft_strappend(&out, ".cor");
		return (out);
	}
}

static t_st extract_name(const char *line)
{
	size_t len;

	len = ft_strlen(NAME_CMD_STRING);
	if (!ft_strncmp(line, NAME_CMD_STRING, len))
	{
		walk += len;
		if (*walk != ' ')
			return st_error;
		return st_succ;
	}
	else
		return st_fail;

}

static t_st extract_comment(const char *line)
{
	return st_succ;
}

static t_st	parse_header(const char *line)
{
	char		*walk;
	t_st		st;
	
	walk = line;
	while (*walk && ft_isspace(*walk))
		walk++;
	if (!*walk)
		return (st_fail);
	else if ((st = extract_name(line)) == st_error)
		return st;
	else if (st && (st = extract_comment(line)))
		return st;
	else
		return (st_succ);
}

t_st		parse_line(const char **line)
{
	char		*instr;

	if (!line || !*line)
		return (st_error);
	else if (parse_header(*line) == st_error)
		return (st_error);
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
			}
			return (st_succ);
		}
	}
}

t_st			read_file(const int ac, const char *av[])
{
	char		*buff;
	char		*outname;
	int			fd;
	t_lst		file;

	if (ac < 2)
	{
		ft_dprintf(2, "no file was provided to %s.", *av);
		return (st_error);
	}
	else if ((outname = filename(av[1])))
		return (st_error);
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_dprintf(2, "no file was provided to %s.", *av);
		return (st_fail);
	}
	else
	{
		file = lst_alloc(blob_free);
		while (gnl(fd, &buff))
			if (parse_line(&buff))
				free(buff);
			else
				lst_push_back_blob(file, buff, sizeof(char *), false);
		return (write_bin(parse_ops(file), outname));
	}
}

t_lst			parse_ops(t_lst lines)
{
	return (NULL);
}

t_st			write_bin(t_lst ops, const char *out)
{
	return st_succ;
}
