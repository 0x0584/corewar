/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:18:08 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:39:31 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "op_impl.h"

struct						s_process
{
	pid_t			pid;
	t_u8			num;
	t_pc			pc;
	t_reg			reg[REG_NUMBER + 1];
	bool			carry;
	t_u16			lives;
	t_op			op;
	t_s32			last_live;
};

void						process_cleanup();
t_proc						new_process(t_u8 num, t_pc at);
t_pc						shift_pc(t_proc p, t_pc offset);
t_pc						pc_shift(t_pc pc, t_pc offset, bool long_op);
t_pc						move_pc(t_proc p, t_pc offset);
t_pc						pc_move(t_pc *pc, t_pc offset, bool long_op);
void						process_dump(void);

const char					*op_disasm(const t_proc proc);
const char					*op_bytecode(const t_op_info *info);

extern pid_t				g_pid;
extern t_lst				g_pool;
extern int					g_fd_check;
#endif
