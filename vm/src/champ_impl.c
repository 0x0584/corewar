/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_impl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:32 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:09:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "champ_impl.h"

static t_st	read_champ(const int fd, t_u8 player_idx, t_champ *champ)
{
	ssize_t				readsz;
	t_u32				null;

	if ((readsz = read(fd, &champ->magic, sizeof(t_u32))) < 0)
		return (st_error);
	else if (beword(champ->magic) != COREWAR_EXEC_MAGIC)
		return (st_fail);
	else if ((readsz = read(fd, champ->prog_name, PROG_NAME_LENGTH)) < 0)
		return (st_error);
	else if ((readsz = read(fd, &null, sizeof(t_u32))) < 0)
		return (st_error);
	else if (null)
		return (st_fail);
	else if ((readsz = read(fd, &champ->prog_size, sizeof(t_u32))) < 0)
		return (st_error);
	else if ((readsz = read(fd, champ->comment, COMMENT_LENGTH)) < 0)
		return (st_error);
	else if ((readsz = read(fd, &null, sizeof(t_u32))) < 0)
		return (st_error);
	else if (null)
		return (st_fail);
	else if ((readsz = read(fd, champ->file, CHAMP_MAX_SIZE)) < 0)
		return (st_error);
	else if ((champ->prog_size = beword(champ->prog_size)) != readsz)
		return (st_fail);
	mem_load(player_idx, champ);
	return (st_succ);
}

t_st		champ_read(const char *filename, t_u8 player_idx, t_champ *champ)
{
	t_st				st;
	int					fd;

	assert(champ != NULL);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (st_error);
	else
		st = read_champ(fd, player_idx, champ);
	close(fd);
	return (st);
}
