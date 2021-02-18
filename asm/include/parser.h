#ifndef PARSER_H
# define PARSER_H

# include "op.h"
# include "champ.h"

t_st			read_file(const int ac, const char *av[]);

t_st			parse_line(char **line);

t_lst			parse_ops(t_lst lines);
t_st			write_bin(t_lst ops, const char *out);

extern t_hash	g_op_lookup;

#endif
