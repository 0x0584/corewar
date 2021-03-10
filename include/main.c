#include "opt.h"

static int g_dump_cycles = 0;

static bool parse_atoi(const char *args[], int at, t_opt *opt)
{
	long	l;
	int		i;

	i = ft_atoi(args[at]);
}

void str_dump(void *blob)
{
	ft_printf("%s\n", blob);
}

static bool opt_prepare(void)
{
	return opt_str_init("dump", 'd', parse_atoi) &&
		opt_init("aff", 'a', false, OPT_NO_ARG);
}

static void opt_dump(void *blob)
{
	t_opt *opt;

	opt = blob;
	ft_printf("long: %s short: %c has_arg\n");
}

int main(int argc, char *argv[])
{
	opt_prepare();
	lst_iter(g_opts, true, opt_dump);
	opt_cleanup();
    return 0;
}
