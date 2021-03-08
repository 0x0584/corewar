#ifndef OPT_H
# define OPT_H

# include "lst.h"

typedef bool			(*opt_arg_callback)(const char *cmd_arg);
typedef	void			(*opt_arg_free)(void *arg);

typedef struct			s_opt_arg
{
	const opt_arg_callback		parse;
	const opt_arg_free			free;
	void						*value;
}						t_opt_arg;

typedef struct			s_opt
{
	const char				*long_opt;
	char					short_opt;

	bool					has_arg;
	t_opt_arg				arg;
}						t_opt;

void					opt_cleanup(void);
bool					opt_init(const char *long_opt, char short_opt,
								 bool has_arg, const t_opt_arg arg);
bool					opt_match(const char *cmd_arg, t_opt *opt);

extern const t_opt_arg	g_no_arg;
extern t_lst			g_opts;

#endif
