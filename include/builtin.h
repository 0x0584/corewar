/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:40:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/03 14:57:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "op_impl.h"

t_u8	nop(t_proc proc);
t_u8	live(t_proc proc);
t_u8	ld(t_proc proc);
t_u8	st(t_proc proc);
t_u8	add(t_proc proc);
t_u8	sub(t_proc proc);
t_u8	and(t_proc proc);
t_u8	or(t_proc proc);
t_u8	xor(t_proc proc);
t_u8	zjmp(t_proc proc);
t_u8	ldi(t_proc proc);
t_u8	sti(t_proc proc);
t_u8	fork_(t_proc proc);
t_u8	lld(t_proc proc);
t_u8	lldi(t_proc proc);
t_u8	lfork(t_proc proc);
t_u8	aff(t_proc proc);

#endif
