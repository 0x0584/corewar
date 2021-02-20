/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:31:42 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 16:34:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

#include "parser.h"

t_u8			arg_valid_types(const t_op *op, t_arg arg);
void			set_op_encoding(t_op *op, t_arg arg, t_u8 type);
bool			ascii_to_digit(const char **astr, char *reg);

t_st			fetch_op_args(t_op *op, const char *args_line);

#endif
