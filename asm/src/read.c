/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:30:44 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 11:51:00 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "compile.h"

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

static char		*read_prepare(const int ac, const char *av[])
{
	char				*outname;

	if (ac < 2)
	{
		st_log(st_error, 2, "no file was provided to %s.", av[0]);
		return (NULL);
	}
	else if (!(outname = filename(av[1])))
	{
		st_log(st_error, 2, "file extension not found %s.\n", av[1]);
		return (NULL);
	}
	else
		return (outname);
}

static t_lst	read_lines(const int fd)
{
	t_lst			file;
	char			*buff;
	t_st			st;

	file = lst_alloc(blob_free);
	st = st_error;
	while (gnl(fd, &buff))
	{
		st = st_fail;
		if (!*buff || (st = parse_line(&buff)))
		{
			free(buff);
			if (st == st_error)
				break ;
		}
		else
		{
			lst_push_back_blob(file, buff, sizeof(char *), false);
			st = st_succ;
		}
	}
	gnl_clean(fd);
	if (st == st_error)
		lst_del(&file);
	return (file);
}

t_st			read_file(const int ac, const char *av[])
{
	t_lst			file;
	char			*outname;
	int				fd;
	t_st			st;

	if (!(outname = read_prepare(ac, av)))
		return (st_error);
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_strdel(&outname);
		return (st_log(st_fail, 2, "cannot open file %s.\n", av[1]));
	}
	if (!(file = read_lines(fd)))
		st = st_error;
	else
	{
		st = compile(file, outname);
		lst_del(&file);
	}
	free(outname);
	close(fd);
	return (st);
}
