/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:58:40 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:40:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "op_impl.h"
# include "champ.h"

# define MAX_OP_NAME						6

t_st			skip_whitespace(const char **ptr);
t_st			match_name(const char *line);
t_st			match_comment(const char *line);
t_st			valid_label(const char *label);
void			set_op_encoding(t_op *op, t_arg arg, t_u8 type);
bool			ascii_to_digit(const char **astr, char *reg);
t_st			fetch_op_args(t_op *op, const char *args_line);
t_st			read_arg(t_op *op, const t_arg arg, const char **arg_line);
t_st			read_reg(t_op *op, const t_arg arg, const char **arg_line);
t_st			read_file(const int ac, const char *av[]);
t_st			parse_line(char **line);
t_st			parse_arg_value(t_op *op, t_arg arg, const char **arg_line);
t_st			parse_op(t_op *op, const char *line, t_st label);
t_lst			parse_ops(t_lst lines);

extern t_hash	g_op_lookup;
extern t_champ	g_champ;
extern int		g_header_status;

#endif
