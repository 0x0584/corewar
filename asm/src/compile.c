#include "compile.h"

struct
{
	const char *op;
	const char *args[MAX_ARGS_NUMBER];
};

static char		g_buff[OP_BUFF_SIZE];		
static t_lst	g_ops = NULL;

static bool		valid_op()
{
	t_u8			i;

	i = 0;
	while (i < op_count)
		if (!ft_strcmp(g_buff, g_op_names[i]))
			return (true);
	return (false);
}

static char		*extract_op(const char *line)
{
	const char		*walk;
	char			*buff_walk;
	
	walk = line;
	buff_walk = buff;

	if (valid_op(buff))
		
}

t_st		    compile(const char *file)
{
	int				fd;
	char			*line;
	char			*
	if ((fd = open(file, O_RDONLY)) < 0)
		return (st_error);
	while (ft_gnl(fd, &line))
	{
		if (*line)
			ft_lst_push_back_blob(g_line, extract_op(line), sizeof line, false);
		ft_strdel(line);		
	}
	return (st_succ);
}
