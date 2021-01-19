#include "player.h"

bool player_debug = true;

static inline t_u8 bebyte(t_u8 byte) { return (byte << 2 | byte >> 2); }

/* Big Endian Word -- 32-bit */
static inline t_u32 beword(t_u32 word) {
    return ((word >> 24) & 0xff) | ((word << 8) & 0xff0000) |
           ((word >> 8) & 0xff00) | ((word << 24) & 0xff000000);
}

int player_read(const char *filename, t_player *p) {
    int fd;
    ssize_t readsz;

    /* --------------------------------------------- */

	int flag = 0;

    if ((fd = open(filename, O_RDONLY)) < 0)
        return -1;
    else if ((readsz = read(fd, p, sizeof(t_header))) < 0)
        flag = -1;
    else if (readsz != sizeof(t_header))
        flag = ft_dprintf(2, "header is corrupted\n");

    if (flag) {
        close(fd);
        return flag;
    }

    /* --------------------------------------------- */

    p->hdr.magic = beword(p->hdr.magic);
    p->hdr.prog_size = beword(p->hdr.prog_size);

    /* --------------------------------------------- */

    if (!(p->file = malloc(p->hdr.prog_size)))
        return -1;
    else if (p->hdr.magic != COREWAR_EXEC_MAGIC)
        flag  = ft_dprintf(2, "file format unknown: %x\n", p->hdr.magic);
    else if ((readsz = read(fd, p->file, p->hdr.prog_size)) < 0)
        flag = -1;
    else if (readsz != p->hdr.prog_size)
        flag = ft_dprintf(2, "binary is altered, prog_size: %u != %ld\n",
                          p->hdr.prog_size, readsz);
    if (flag) {
        free(p->file);
        p->file = NULL;
    } else {
        close(fd);
    }

	t_u32 i = 0;
	while (i < p->hdr.prog_size)
	{
		p->file[i] = bebyte(p->file[i]);
		i++;
	}

    /* --------------------------------------------- */

    if (player_debug) {
        ft_printf("prog name: %s\n", p->hdr.prog_name);
        ft_printf("prog size: %u Byte\n", p->hdr.prog_size);
        ft_printf("comment: %s\n", p->hdr.comment);

        /* int tab[10] = {0, 23, 150, 255, 12, 16, 42, 103}; */
        /* print_memory(tab, sizeof(tab)); */

        print_memory(p->file, p->hdr.prog_size);
    }

    /* --------------------------------------------- */
    return 0;
}

void player_delete(t_player *p) {
    if (!p) {
        free(p->file);
        p->file = 0;
    }
}

int main(int argc, char *argv[]) {
    t_player foo;
	int st;

    for (int i = 1; i < argc; ++i)
		if ((st = player_read(argv[i], &foo)) < 0)
			return -1;
		else if (st)
			continue;
		else
			player_delete(&foo);
    return 0;
}
