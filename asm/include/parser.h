#ifndef PARSER_H
# define PARSER_H

# include "op.h"
# include "champ.h"

typedef struct		s_operation
{
	t_op_meta				meta;
	t_op_encoding			encoded;
	t_blob					args;
}					t_op;

t_st			read_file(const int ac, const char *av[]);

t_st			parse_line(char **line);
t_st			parse_op(t_op *op, const char *buff);

t_lst			parse_ops(t_lst lines);
t_st			write_bin(t_lst ops, const char *out);

#endif
