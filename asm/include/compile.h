/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:06:11 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 11:46:15 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPILE_H
# define COMPILE_H

# include "parser.h"

t_u8			arg_offset(const t_op_info *info, t_arg arg);
t_s16			write_arg(const t_op_info *info, const t_arg arg, t_s16 at);
void			write_op(void *blob, void *size);

t_st			write_prog(t_lst ops);

t_st			compile(t_lst lines, const char *outname);

#endif
