#include "libft.h"
#include "op.h"

static inline t_u8 bebyte(t_u8 byte) { return (byte << 2 | byte >> 2); }

/* Big Endian Word -- 32-bit */
static inline t_u32 beword(t_u32 word) {
    return ((word >> 24) & 0xff) | ((word << 8) & 0xff0000) |
           ((word >> 8) & 0xff00) | ((word << 24) & 0xff000000);
}

int main(int argc, char *argv[]) {
    t_header hdr;
    ssize_t readsz;

    /* --------------------------------------------- */

    if ((readsz = read(STDIN_FILENO, &hdr, sizeof(t_header))) < 0)
        return -1;
    else if (readsz != sizeof(t_header))
        return ft_dprintf(2, "header is corrupted\n");

    /* --------------------------------------------- */

    hdr.magic = beword(hdr.magic);
    hdr.prog_size = beword(hdr.prog_size);

    /* --------------------------------------------- */

    t_u8 *cor = malloc(hdr.prog_size);

    if (hdr.magic != COREWAR_EXEC_MAGIC)
        return ft_dprintf(2, "file format unknown: %x\n", hdr.magic);
    else if ((readsz = read(STDIN_FILENO, cor, hdr.prog_size)) < 0)
        return -1;
    else if (readsz != hdr.prog_size)
        return ft_dprintf(2, "binary is altered, prog_size: %u != %ld\n",
                          hdr.prog_size, readsz);

    /* --------------------------------------------- */

    ft_printf("prog name: %s\n", hdr.prog_name);
    ft_printf("prog size: %u Byte\n", hdr.prog_size);
    ft_printf("prog size: %s\n", hdr.comment);

    int tab[10] = {0, 23, 150, 255, 12, 16, 42, 103};

    print_memory(tab, sizeof(tab));

    print_memory(cor, hdr.prog_size);

    /* --------------------------------------------- */

    return 0;
}
