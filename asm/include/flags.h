#ifndef FLAGS_H
# define FLAGS_H

struct					s_flags
{
	bool		verbose;
	const char	*file;
};

t_st					parse_arguments(int ac, char *av[]);

extern struct s_flags	g_flags;

#endif
