#include "libft.h"
#include "op.h"

static inline t_u8 bebyte(t_u8 byte) {
	return (byte << 2 | byte >> 2);
}

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
	else if (hdr.magic != beword(COREWAR_EXEC_MAGIC))
		return ft_dprintf(2, "file format unknown: %x\n", hdr.magic);

	/* --------------------------------------------- */

	hdr.prog_name[PROG_NAME_LENGTH] = '\0';
	hdr.comment[COMMENT_LENGTH] = '\0';
	ft_printf("prog name: %s\n", hdr.prog_name);
	ft_printf("prog size: %u Byte\n", beword(hdr.prog_size));
	ft_printf("prog size: %s\n", hdr.comment);

	/* --------------------------------------------- */


    return 0;
}
