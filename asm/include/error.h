#ifndef ERROR_H
# define ERROR_H

# include "libft.h"

typedef void	(*t_err_callback(void *));

enum			e_error
{
	err_no_file = -1,
	err_too_many_args,
	
};

enum e_error	error_raise(enum e_error err, t_err_callback callback, void *arg);

void			print_usage(void *arg);

#endif
