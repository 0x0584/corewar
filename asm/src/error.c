#include "error.h"

enum e_error	error_raise(enum e_error err, t_err_callback callback, void *arg)
{
	callback(arg);
	return err;
}
