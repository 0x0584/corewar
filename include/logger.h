#ifndef LOGGER_H
# define LOGGER_H

# include <assert.h>

# include "libft.h"

/**
** \brief return status of all vm routines
*/
typedef enum				e_state
{
    /**
    ** \brief in case of a fatal error, such as a failure of a syscall
    */
    st_error = -1,

    /**
    ** \brief in case of a success, such as the callee did what the caller
    ** expected
    */
    st_succ,

    /**
    ** \brief in case of an error, but not fatal. such as an illegal execute of
    ** an operation
    */
    st_fail
}							t_st;

t_st						st_log(t_st st, int fd, const char *fmt, ...);

#endif
