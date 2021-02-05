/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/05 16:37:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "draw.h"

static t_st			read_player(const int fd, t_u8 player_num)
{
    ssize_t		readsz;
	t_player	*player;

	player = g_vm.gladiators + player_num;
    if ((readsz = read(fd, player, sizeof *player)) < 0)
        return LOGGER(st_error, "invalid read from %d\n", fd);
    /* else if (readsz != sizeof *player) */
	/* 	return LOGGER(st_fail, "header of player %d is corrupted\n", player_num); */

	player_dump(&g_vm.gladiators[player_num]);

    player->champ.magic = beword(player->champ.magic);
    player->champ.prog_size = beword(player->champ.prog_size);

	if (player->champ.magic != COREWAR_EXEC_MAGIC)
        return LOGGER(st_error, "file format unknown: %x\n", ch->magic);
	else if (player->champ.file[player->champ.prog_size])
       return LOGGER(st_fail, "binary is altered, prog_size: %u %08x\n", ch->prog_size,
					 player->champ.file[player->champ.prog_size]);
	else
		return LOGGER(st_succ, "read player %d (fd: %d)\n", player_num, fd);
}

void				player_dump(t_player *p)
{
    if (g_player_debug)
	{
        LOGGER(st_succ, "prog name: %s\n", p->champ.prog_name);
        LOGGER(st_succ, "prog size: %u Byte\n", p->champ.prog_size);
        LOGGER(st_succ, "comment: %s\n", p->champ.comment);

        print_memory(&p->champ, sizeof(t_champ));
		ft_putendl("------------------------");
    }
}

t_st				player_read(const char *filename, t_u8 player_num)
{
    t_st	st;
    int		fd;

	assert(player_num < MAX_PLAYERS);
    if ((fd = open(filename, O_RDONLY)) < 0)
        return (st_error);
    else if (!(st = read_player(fd, player_num)))
		player_dump(&g_vm.gladiators[player_num]);
    close(fd);
    return (st);
}

bool				g_player_debug = true;
