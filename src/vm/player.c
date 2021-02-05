/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/05 18:05:16 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "draw.h"

static t_st			check_player(ssize_t readsz, const t_player *player)
{
	if (player->champ.magic != COREWAR_EXEC_MAGIC)
        return LOGGER(st_error, "file format unknown: %x\n", player->champ.magic);
	else if (player->champ.prog_size != readsz - (sizeof *player - CHAMP_MAX_SIZE))
		return LOGGER(st_fail, "binary is altered, prog_size: %u %08x\n",
					  player->champ.prog_size, player->champ.file[player->champ.prog_size]);
	else
		return st_succ;
}

static t_st			read_player(const int fd, t_u8 player_num)
{
    ssize_t		readsz;
	t_player	*player;
	t_st		st;

	player = g_vm.gladiators + player_num;


    if ((readsz = read(fd, &player->champ.magic, sizeof(t_u32))) < 0)
		return st_error;
	else if (beword(player->champ.magic) != COREWAR_EXEC_MAGIC)
		return st_error;
	else if ((readsz = read(fd, player->prog_name, PROG_NAME_LENGTH)) < 0)
		return st_error;
	else if ((readsz = read(fd, &player->champ.prog_size, sizeof(t_u32))) < 0)
		return st_error;
	else if (player->champ.prog_size)
		return st_error;
	else if ((readsz = read(fd, &player->champ.prog_size, sizeof(t_u32))) < 0)
		return st_error;
	else if ((readsz = read(fd, &player->champ.comment, COMMENT_LENGTH)) < 0)
		return st_error;
	else if ((readsz = read(fd, &player->champ.file, CHAMP_MAX_SIZE)) < 0)
		return st_error;
	else if (*(t_u32 *)player->champ.file)
		return st_error;
	else

	player_dump(&g_vm.gladiators[player_num]);

    player->champ.magic = beword(player->champ.magic);
    player->champ.prog_size = beword(player->champ.prog_size);

	mem_load(player->champ.file, player_num);

	if ((st = check_player(readsz, player)))
		return (st);
	else
		return (LOGGER(st_succ, "read player %d (fd: %d)\n", player_num, fd));
}

void				player_dump(t_player *p)
{
    if (g_player_debug)
	{
        print_memory(&p->champ, sizeof(t_champ));

        LOGGER(st_succ, "prog name: %s\n", p->champ.prog_name);
        LOGGER(st_succ, "prog size: %u Byte\n", p->champ.prog_size);
        LOGGER(st_succ, "comment: %s\n", p->champ.comment);
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
