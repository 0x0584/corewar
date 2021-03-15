/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_meta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:42:22 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 08:42:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_impl.h"

bool		op_meta_short(const t_op *op)
{
	return (op && op->info.meta.of.short_chunk);
}

bool		op_meta_long(const t_op *op)
{
	return (op && op->info.meta.of.long_op);
}
