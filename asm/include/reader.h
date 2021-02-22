/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:30:51 by archid-           #+#    #+#             */
/*   Updated: 2021/02/20 17:35:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "parser.h"

t_st			read_arg(t_op *op, const t_arg arg, const char **arg_line);

t_st			read_reg(t_op *op, const t_arg arg, const char **arg_line);
t_st			read_dir(t_op *op, const t_arg arg, const char **arg_line);
t_st			read_ind(t_op *op, const t_arg arg, const char **arg_line);
void			read_label_or_value(const char *prefix, t_arg *type);

t_st			read_file(const int ac, const char *av[]);

#endif
