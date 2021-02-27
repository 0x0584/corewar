/* compile: gcc foo.c -o foo -Ilibft -lft -Llibft */

#include <assert.h>
#include "libft.h"

#ifdef BUFF_SIZE
# undef BUFF_SIZE
#endif
#define BUFF_SIZE 2 * (sizeof(long) + sizeof(int) + sizeof(short) + sizeof(char))

union value
{
	long int			lval;
	unsigned long		ulval;
	int					ival;
	unsigned int		uival;
	short				sval;
	unsigned short		usval;
	char				val;
	unsigned char		uval;
};

static void	dump_value(union value val);

static unsigned char buff[BUFF_SIZE];

#define lseek 	lseek(fd, offset, SEEK_SET)
int	main(int argc, const char *argv[])
{

	if (argc != 2)
		return ft_printf("%s N\n", *argv);

	const union value val = {.lval = ft_atol(argv[1])};
	register const int fd = open("cor", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	register off_t offset = -write(fd, buff, sizeof buff);

	dump_value(val);
	printf("%ld", offset);

	offset += sizeof(char);
	lseek, offset += write(fd, &val.val, sizeof(char));
	lseek, offset += write(fd, &val.uval, sizeof(char));

	offset += sizeof(short);
	lseek, offset += write(fd, &val.sval, sizeof(short));
	lseek, offset += write(fd, &val.usval, sizeof(short));

	offset += sizeof(int);
	lseek, offset += write(fd, &val.ival, sizeof(int));
	lseek, offset += write(fd, &val.uival, sizeof(int));

	offset += sizeof(long);
	lseek, offset += write(fd, &val.lval, sizeof(long));
	write(fd, &val.ulval, sizeof(long));
	close(fd);

	return 0;
}
#undef lseek

static void	dump_value(union value val)
{
	ft_printf("%8s | %8s | %8s\n", "type", "signed", "unsigned");
	ft_printf("%8s   %8s   %8s\n", "", "", "");
	ft_printf("%8s | %8ld | %8lu\n", "long", val.lval, val.ulval);
	ft_printf("%8s | %08x | %08x\n", "", val.lval, val.ulval);
	ft_printf("%8s | %8d | %8u\n", "int", val.ival, val.uival);
	ft_printf("%8s | %08x | %08x\n", "", val.ival, val.uival);
	ft_printf("%8s | %8hd | %8hu\n", "short", val.sval, val.usval);
	ft_printf("%8s | %08x | %08x\n", "", val.sval, val.usval);
	ft_printf("%8s | %8hhd | %8hhu\n", "char", val.val, val.uval);
	ft_printf("%8s | %08x | %08x\n", "", val.val, val.uval);
}
