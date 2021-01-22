/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:32 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 16:38:25 by archid-          ###   ########.fr       */
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

static t_st			read_file_header(const int fd, t_player *p)
{
    ssize_t readsz;
    t_st	st;

    st = st_succ;
    if ((readsz = read(fd, p, sizeof(t_header))) < 0)
        st = st_error;
    else if (readsz != sizeof(t_header))
	{
        st = st_fail;
        ft_dprintf(2, "header is corrupted\n");
    }
    p->hdr.magic = beword(p->hdr.magic);
    p->hdr.prog_size = beword(p->hdr.prog_size);
    return (st);
}

static t_st			read_prog(const int fd, t_player *p)
{
    ssize_t readsz;
    t_st	st;

    st = 0;
    if (!(p->file = malloc(p->hdr.prog_size)))
        return (st_error);
    else if (p->hdr.magic != COREWAR_EXEC_MAGIC)
	{
        st = st_fail;
        ft_dprintf(2, "file format unknown: %x\n", p->hdr.magic);
    } else if ((readsz = read(fd, p->file, p->hdr.prog_size)) < 0)
        st = st_fail;
    else if (readsz != p->hdr.prog_size)
	{
        st = st_fail;
        ft_dprintf(2, "binary is altered, prog_size: %u != %ld\n",
                   p->hdr.prog_size, readsz);
    }
    if (st)
	{
        free(p->file);
        p->file = NULL;
    }
    return (st);
}

void				player_dump(t_player *p)
{
    if (g_player_debug)
	{
        ft_printf("prog name: %s\n", p->hdr.prog_name);
        ft_printf("prog size: %u Byte\n", p->hdr.prog_size);
        ft_printf("comment: %s\n", p->hdr.comment);
        print_memory(&p->hdr, sizeof(t_header));
        print_memory(p->file, p->hdr.prog_size);
    }
}

t_st				player_read(const char *filename, t_player *p)
{
    t_st	st;
    int		fd;

    if ((fd = open(filename, O_RDONLY)) < 0)
        return (st_error);
    else if (!(st = read_file_header(fd, p)))
        if (!(st = read_prog(fd, p)))
            player_dump(p);
    close(fd);
    return (st);
}

void				player_delete(t_player *p)
{
    if (!p)
	{
        free(p->file);
        p->file = 0;
    }
}

bool				g_player_debug = true;
