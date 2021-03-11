/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:30:44 by archid-           #+#    #+#             */
/*   Updated: 2021/02/26 10:07:35 by archid-          ###   ########.fr       */
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

t_st			read_file(const int ac, const char *av[])
{
	t_lst			file;
	int				fd;
	char			*buff;
	char			*outname;
	t_st			st;

	if (ac < 2)
	{
		ft_dprintf(2, "no file was provided to %s.\n", av[0]);
		return (st_error);
	}
	else if (!(outname = filename(av[1])))
		return (st_error);
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_dprintf(2, "cannot open file\n", av[1]);
		free(outname);
		return (st_fail);
	}
	file = lst_alloc(blob_free);
	while (gnl(fd, &buff))
	{
		st = st_fail;
		if (!*buff || (st = parse_line(&buff)))
		{
			free(buff);
			if (st == st_error)
			{
				lst_del(&file);
				break;
			}
		}
		else
			lst_push_back_blob(file, buff, sizeof(char *), false);
	}
	gnl_clean(fd);
	st = compile(file, outname);
	lst_del(&file);
	free(outname);
	close(fd);
	return st;
}
