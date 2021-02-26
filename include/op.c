#include "op.h"

char		*op_bytecode(const t_op_info *info)
{
	char *bytecode;

	ft_asprintf(&bytecode, "%02 ", info->code);
	return bytecode;
}
