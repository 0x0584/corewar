/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 11:54:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "draw.h"

static t_st			read_champ(const int fd, t_u8 player_num, t_player *player)
{
    ssize_t				readsz;
	t_champ				champ;
	t_u32				null;

    if ((readsz = read(fd, &champ.magic, sizeof(t_u32))) < 0)
		return st_error;
	else if (beword(champ.magic) != COREWAR_EXEC_MAGIC)
		return st_fail;
	else if ((readsz = read(fd, player->prog_name, PROG_NAME_LENGTH)) < 0)
		return st_error;
	else if ((readsz = read(fd, &null, sizeof(t_u32))) < 0)
		return st_error;
	else if (null)
		return st_fail;
	else if ((readsz = read(fd, &champ.prog_size, sizeof(t_u32))) < 0)
		return st_error;
	else if ((readsz = read(fd, &champ.comment, COMMENT_LENGTH)) < 0)
		return st_error;
	else if ((readsz = read(fd, &null, sizeof(t_u32))) < 0)
		return st_error;
	else if (null)
		return st_fail;
	else if ((readsz = read(fd, &champ.file, CHAMP_MAX_SIZE)) < 0)
		return st_error;
	else if ((champ.prog_size = beword(champ.prog_size)) != readsz)
		return st_fail;
	mem_load(player_num, player, &champ);
	return st_succ;
}

t_st				player_read(const char *filename, t_u8 player_num, t_player *player)
{
    t_st				st;
    int					fd;

	assert(player != NULL);
    if ((fd = open(filename, O_RDONLY)) < 0)
        return (st_error);
    else
		st = read_champ(fd, player_num, player);
    close(fd);
    return (st);
}
