/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:40:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/07 12:19:52 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "vm.h"
#include "process.h"

void	nop(t_proc proc);
void	live(t_proc proc);
void	ld(t_proc proc);
void	st(t_proc proc);
void	add(t_proc proc);
void	sub(t_proc proc);
void	and(t_proc proc);
void	or(t_proc proc);
void	xor(t_proc proc);
void	zjmp(t_proc proc);
void	ldi(t_proc proc);
void	sti(t_proc proc);
void	fork_(t_proc proc);
void	lld(t_proc proc);
void	lldi(t_proc proc);
void	lfork(t_proc proc);
void	aff(t_proc proc);

#endif
