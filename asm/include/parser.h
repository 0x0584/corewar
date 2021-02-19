#ifndef PARSER_H
# define PARSER_H

# include "op.h"
# include "champ.h"

# define MAX_OP_NAME						5

t_st			read_file(const int ac, const char *av[]);

t_st			parse_line(char **line);
t_lst			parse_ops(t_lst lines);

t_st			match_name(const char *line);
t_st			match_comment(const char *line);

extern t_hash	g_op_lookup;
extern t_champ	g_champ;
extern int		g_header_status;
extern t_u8		g_name[PROG_NAME_LENGTH + 1];

#endif
