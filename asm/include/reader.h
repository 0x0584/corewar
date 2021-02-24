/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:30:51 by archid-           #+#    #+#             */
/*   Updated: 2021/02/24 10:57:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "parser.h"

t_st			read_arg(t_op *op, const t_arg arg, const char **arg_line);

t_st			read_arg_label(t_op *op, t_arg arg, const char **arg_line);
t_st			read_arg_value_base(t_op *op, t_arg arg, const char **arg_line);
t_st			read_reg(t_op *op, const t_arg arg, const char **arg_line);

t_st			read_file(const int ac, const char *av[]);

#endif
