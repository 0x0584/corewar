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

typedef struct	s_operation
{
	t_op_info			info;
	t_u16				addr;
	const char			*labels[MAX_ARGS_NUMBER];
}				t_op;

extern t_hash	g_labels;
extern t_u16	g_max_op_length;

#endif
