#ifndef DIS_H
# define DIS_H

#include "libft.h"
#include "op.h"

typedef t_u8 *t_addr;
typedef t_u32 t_reg;
typedef t_u32 t_dir;
typedef t_u16 t_idr;

typedef struct s_process {
    bool carry;
    t_addr pc;
    t_reg reg[REG_NUMBER];
} t_player;

union u_arg {
    t_u8 u8;
    t_u16 u16;
    t_u32 u32;
};

typedef bool (*op_callback_t)(t_player, union u_arg[MAX_ARGS_NUMBER], t_u8);

typedef struct op {
    t_u8 encoding;
    union u_arg args[MAX_ARGS_NUMBER];
    op_callback_t instr;
} op_t;

enum e_errors {
    invalid_arguments,

    error_count
};

extern const char	*g_errstr[error_count];
extern t_u8			g_memory[MEM_SIZE];
extern t_u16		g_errno;

#endif
