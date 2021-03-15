/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:52:32 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:35:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "vm.h"

void		mem_load(t_u8 player_idx, const t_champ *champ);
t_st		handle_chunk(t_proc p, t_arg arg, t_pc *offset);
void		mem_write_chunk(const t_proc p, const union u_chunk *chnk,
							t_pc offset);
void		mem_read_chunk(const t_proc p, union u_chunk *chnk,
							bool read_reg_size, t_pc offset);
t_st		read_arg_chunk(t_proc p, t_pc *offset);
void		mem_chunk(t_proc p, t_arg arg, t_pc *offset);
t_u8		mem_deref(t_proc p, t_pc offset);
t_u8		mem_at(t_proc p);
t_u8		at_mem(t_pc p);
t_arg		encoded(t_u8 arg_code);
t_dir		arg_value(t_proc proc, t_arg arg, bool deref);
t_u32		beword(t_u32 word);
t_u8		bebyte(t_u8 byte);

#endif
