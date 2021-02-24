#ifndef WRITER_H
# define WRITER_H

# include "parser.h"

t_u8			arg_offset(const t_op_info *info, t_arg arg);
t_s16			write_arg(const t_op_info *info, const t_arg arg, t_s16 at);
void			write_op(void *blob, void *size);

t_st			write_prog(t_lst ops);

#endif
