/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:06:01 by archid-           #+#    #+#             */
/*   Updated: 2021/02/19 15:57:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_IMPL_H
# define OP_IMPL_H

# include "delimiter.h"

# define ARG_BASE_BIN		1
# define ARG_BASE_OCT		2
# define ARG_BASE_DEC		4
# define ARG_BASE_HEX		8

typedef union	u_args_base
{
	t_u16					mask;

	struct		s_bases
	{
		t_u8	arg1:4;
		t_u8	arg2:4;
		t_u8	arg3:4;
		t_u8	padding:4;
	}						base;
}				t_args_base;

typedef struct	s_operation
{
	t_op_info			info;
	t_u16				addr;
	const char			*labels[MAX_ARGS_NUMBER];
}				t_op;

t_st			compile(t_lst lines, const char *outname);

extern t_hash	g_labels;
extern t_u16	g_max_op_length;

#endif
