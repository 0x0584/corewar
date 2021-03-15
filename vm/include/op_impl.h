/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2021/03/15 09:38:30 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
#ifndef OP_IMPL_H
# define OP_IMPL_H

# include "op.h"

typedef t_s32				t_reg;
typedef t_s16				t_pc;
typedef struct s_process	*t_proc;
typedef void				(*t_op_callback)(t_proc proc);
typedef struct				s_operation
{
	t_op_info			info;
	const t_op_callback	callback;
	t_s16				cycles;
}							t_op;

void						callback(void *proc);
void						set_nop(t_proc p);
void						set_ops(void);

extern t_op					g_op[op_count];

#endif
