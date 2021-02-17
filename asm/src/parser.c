#include "parser.h"


static char		*file_name(const char *in)
{
	char		*out;
	char		*ext;
	
	if ((ext = ft_strrchr(in, '.')))
	{
		out = ft_strrdup(in, ext);
		ft_strappend(&out, ".cor");
		return (out);
	}
	else
	{
		return (NULL);
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
		file = lst_init(blob_free);
		while (gnl(fd, &buff))
			if (parse_line(buff))
				free(buff);
			else
				lst_push_back_blob(file, buff, sizeof(char *), false);
		return (write_bin(parse_file(file), outname));
	}
}


t_st			parse_file(t_lst lines, const char *filename)
{
	t_lstnode		walk;
	walk = write_header();
	
	return (st_succ);
}

t_st			write_bin(t_lst ops, const char *out)
{
	
}
