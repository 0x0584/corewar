#ifndef COMPILE_H
# define COMPILE_H

# include "op.h"
# include "champ.h"

# define OP_BUFF_SIZE				32

t_st		    compile(const char *file);

extern t_lst	g_lines;

#endif
