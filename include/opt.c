#include "opt.h"

static inline void	match_opt(void *blob, void *arg)
{

}

bool				opt_init(const char *long_opt, char short_opt,
							 bool has_arg, const t_opt_arg arg)
{
	t_opt				opt;

	if (!g_opts)
		g_opts = lst_alloc(arg.free);

	opt.long_opt = long_opt;
	opt.short_opt = short_opt;
	opt.has_arg = has_arg;
	ft_memcpy(&opt.arg, &arg, sizeof(t_opt_arg));
	return false;
}

bool				opt_match(const char *cmd_arg, t_opt *opt)
{
	return false;
}

void				opt_cleanup(void)
{
	lst_del(&g_opts);
}

const t_opt_arg		g_no_arg;
t_lst				g_opts = NULL;
