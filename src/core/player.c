/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:32 by archid-           #+#    #+#             */
/*   Updated: 2021/01/23 11:41:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "draw.h"

static inline t_u8	bebyte(t_u8 byte)
{
	return (byte << 2 | byte >> 2);
}

/* Big Endian Word -- 32-bit */
static inline t_u32 beword(t_u32 word)
{
    return (((word >> 24) & 0xff) | ((word << 8) & 0xff0000) |
			((word >> 8) & 0xff00) | ((word << 24) & 0xff000000));
}

static t_st			read_header(const int fd, t_header *hdr)
{
    ssize_t readsz;
    t_st	st;

    st = st_succ;
    if ((readsz = read(fd, hdr, sizeof(t_header))) < 0)
        st = st_error;
    else if (readsz != sizeof(t_header))
	{
        st = st_fail;
        ft_dprintf(2, "header is corrupted\n");
    }
    hdr->magic = beword(hdr->magic);
    hdr->prog_size = beword(hdr->prog_size);
    return (st);
}

static t_st			read_champ(const int fd, t_champ *ch)
{
    ssize_t readsz;
    t_st	st;

    st = 0;
    if (ch->hdr.magic != COREWAR_EXEC_MAGIC)
	{
        st = st_fail;
        ft_dprintf(2, "file format unknown: %x\n", ch->hdr.magic);
    } else if ((readsz = read(fd, ch->file, ch->hdr.prog_size)) < 0)
        st = st_fail;
    else if (readsz != ch->hdr.prog_size)
	{
        st = st_fail;
        ft_dprintf(2, "binary is altered, prog_size: %u != %ld\n",
                   ch->hdr.prog_size, readsz);
    }
    return (st);
}

void				player_dump(t_player *p)
{
    if (g_player_debug)
	{
        ft_printf("prog name: %s\n", p->champ.hdr.prog_name);
        ft_printf("prog size: %u Byte\n", p->champ.hdr.prog_size);
        ft_printf("comment: %s\n", p->champ.hdr.comment);
        print_memory(&p->champ, sizeof(t_champ));
    }
}

t_st				player_read(const char *filename, t_player *p)
{
    t_st	st;
    int		fd;

    if ((fd = open(filename, O_RDONLY)) < 0)
        return (st_error);
    else if (!(st = read_header(fd, &p->champ.hdr)))
        if (!(st = read_champ(fd, &p->champ)))
            player_dump(p);
    close(fd);
    return (st);
}

bool				g_player_debug = false;
